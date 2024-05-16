/*************************************************************************
 *
 *  sis3820_list.c -   Library of routines for readout and buffering of
 *                     events using a JLAB Trigger Interface V3 (TI) with
 *                     a Linux VME controller in CODA 3.0.
 *                    
 *                     This is a ROL for the sis3820 scaler. It uses the 
 *                     a TI rol as the base with the added output of the 
 *                     scaler
 */

/****************************
 *       TI Specifics       *
 ***************************/
/* Event Buffer Definitions */
#define MAX_EVENT_POOL   200
#define MAX_EVENT_LENGTH 1024*40 /* size in bytes */

/* Define TI Type */
#define TI_SLAVE
/* TS Fiber Link trigger source (from TI Master, TD, or TS), POLL for available data */
#define TI_READOUT TI_READOUT_TS_POLL

/* TI VME address, or 0 for Auto Initialize (search for TI by slot) */
#define TO_ADDR 0
/* Measured longest fiber length in systemt */
#define FIBER_LATENCY_OFFSET 0x4A

/* Define buffering level */
#define BUFFERLEVEL 10

/* Headers */
#include "dmaBankTools.h"   /* Macros for handling CODA banks            */
#include "tiprimary_list.c" /* Source required for CODA ROL using the TI */
#include "sdLib.h"

/****************************************
 *  DOWNLOAD
 ****************************************/
void rocDownload()
{
	int stat;
	/* Setup Address and data modes for DMA transfers
	 *
	 *  vmeDmaConfig(addrType, dataType, sstMode);
	 *
	 *  addrType = 0 (A16)    1 (A24)    2 (A32)
	 *  dataType = 0 (D16)    1 (D32)    2 (BLK32) 3 (MBLK) 4 (2eVME) 5 (2eSST)
	 *  sstMode  = 0 (SST160) 1 (SST267) 2 (SST320)
	 */
	vmeDmaConfig(2,1,1);


	/* Define Block Level */
	blockLevel = 1;

	/* Set Trigger Source */
	//tiSetTriggerSourceMask(5|10|1|2|4|3|7); // RANDOM TRIGGER
	//tiEnableTriggerSource();
	//tiSetSlavePort(5);
      	/* Enable HFBR#5 */
      	tiEnableFiber(5);
      	/* HFBR#5 Clock Source */
      	tiSetClockSource(1);
      	/* HFBR#5 Sync Source */
      	tiSetSyncSource(TI_SYNC_HFBR5);
      	/* HFBR#5 Trigger Source */
      	tiSetTriggerSource(TI_TRIGGER_HFBR5);
	tiSetTriggerSourceMask(TI_TRIGGER_HFBR5 );
	tiEnableTriggerSource();
/*
	stat = sdInit(0);	
	if(stat == 0)
	{
		sdSetActiveVmeSlots(0);
		sdStatus(0);
	}
*/
	tiStatus(0);
	printf("TI Initilized\n");
	printf("--------\n");
	printf("rocDownload: etclient.c Downloaded Executed");
} /* end Download */

/****************************************
 *  PRESTART
 ****************************************/
void
rocPrestart()
{
	/* Set number of events per block */
	// tiSetBlockLevel(blockLevel);
	printf("rocPrestart: Block Level set to %d\n",blockLevel);
	unsigned int fiber_port = 5;
	printf("rocPrestart: Added tiClient connected to fiber port %d\n",fiber_port);
	// tiFakeTriggerBankOnError(1);
	tiStatus(0);

	/* EXAMPLE: User bank of banks added to prestart event */
	UEOPEN(500,BT_BANK, 0);

	/* EXAMPLE: Bank of data in User Bank 500 */
	CBOPEN(1, BT_UI4, 0);
	CBWRITE32(0xda000011);
	*rol->dabufp++ = 0x11112222;
	*rol->dabufp++ = 0x55556666;
	*rol->dabufp++ = 0xaabbccdd;
	CBWRITE32(0xda0000ff);	
	CBCLOSE;
	
	UECLOSE;

	printf("rocPrestart: ti client Prestart Executed");
} /* end Prestart */


/****************************************
 *  GO
 ****************************************/
void
rocGo()
{
	/* Print Run Number and Run Type (config ID) */
	printf("rocGo: Activating Run Number %d, Config id = %d\n",
			rol->runNumber,rol->runType);

	/* Get the broadcasted Block and Buffer Levels from TS or TI Master */
	blockLevel = tiGetCurrentBlockLevel();
  	bufferLevel = tiGetBroadcastBlockBufferLevel();
	printf("rocGo: Block Level set to %d  Buffer Level set to %d\n",blockLevel,bufferLevel);
	/* In case of slave, set TI busy to be enabled for full buffer level */
	tiUseBroadcastBufferLevel(1);
  	// tiSetRandomTrigger(1,0xe);
} /* end Go */

/****************************************
 *  END
 ****************************************/
void
rocEnd()
{
  	tiDisableRandomTrigger();
	tiStatus(0);
	printf("rocEnd: Ended after %d blocks\n",tiGetIntCount() );
} /* end rocEnd */

/****************************************
 *  TRIGGER
 ****************************************/
void
rocTrigger(int evntno)
{

	static int counter;
	printf("\nTrigger %d Received From Master\n",counter);
	counter++;

	int dCnt, idata, stat;
	int nwords;
	tiSetOutputPort(1,0,0,0);

	/* Check if this is a Sync Event */
	stat = tiGetSyncEventFlag();
	if(stat) {
		printf("rocTrigger: Got Sync Event!! Block # = %d\n",evntno);
	}


	dCnt = tiReadTriggerBlock(dma_dabufp);	
	if(dCnt <= 0 ) printf("No TI Trigger data or Error... dCnt = %d\n", dCnt);
	else
	{
		int i;
		for(i = 0; i < dCnt; i++){
			printf("dma_dabufp = %#04x\n", *dma_dabufp);	
			dma_dabufp++;
		}	
	}

	/* EXAMPLE: How to open a bank (name=5, type=ui4) and add data words by hand */
	BANKOPEN(4,BT_UI4,blockLevel);
	*dma_dabufp++ = tiGetIntCount();
	*dma_dabufp++ = 0x44;
	*dma_dabufp++ = 0x0044;
	*dma_dabufp++ = 0x000044;
	int ii;
	for (ii=1;ii<=50;ii++) {
		*dma_dabufp++ = ii;
	}
	*dma_dabufp++ = 0xcebaf222;
	BANKCLOSE;

	/* Check for sync Event */
	if(tiGetSyncEventFlag()) {
		/* Set new block level if it has changed */
		idata = tiGetCurrentBlockLevel();
		if((idata != blockLevel)&&(idata<255)) {
			blockLevel = idata;
			printf("rocTrigger: Block Level changed to %d\n",blockLevel);
		}

		/* Clear/Update Modules here */
	}

	tiSetOutputPort(0,0,0,0);

} /* end rocTrigger */

void
rocCleanup()
{
	printf("%s: Reset all Modules\n", __FUNCTION__);
} /* end rocCleanup */
