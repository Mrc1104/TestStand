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
#define MAX_EVENT_POOL   10
#define MAX_EVENT_LENGTH 1024*64 /* size in bytes */
/* Define TI Type */
#define TI_MASTER
/* External trigger source (e.g. front panel ECL input), POLL for available data */
#define TI_READOUT TI_READOUT_EXT_POLL
/* TI VME address, or 0 for Auto Initialize (search for TI by slot) */
#define TO_ADDR 0
/* Measured longest fiber length in systemt */
#define FIBER_LATENCY_OFFSET 0x4A

/* Headers */
#include "dmaBankTools.h"   /* Macros for handling CODA banks            */
#include "tiprimary_list.c" /* Source required for CODA ROL using the TI */
#include "sdLib.h"

/* Define intiial blocklevel and buffering level */
#define BLOCKLEVEL  1
#define BUFFERLEVEL 10

#define INTRANDOMPULSER

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
	vmeDmaConfig(2,5,1);


	/*****************
	 *   TI SETUP    *
	 *****************/
	
	/* Define Block Level */
	blockLevel = BLOCKLEVEL;

	/*
	 * Set Trigger source
	 *    For the TI-Master, valid sources:
	 *      TI_TRIGGER_FPTRG     2  Front Panel "TRG" Input
	 *      TI_TRIGGER_TSINPUTS  3  Front Panel "TS" Inputs
	 *      TI_TRIGGER_TSREV2    4  Ribbon cable from Legacy TS module
	 *      TI_TRIGGER_PULSER    5  TI Internal Pulser (Fixed rate and/or random)
	 */
  	tiSetTriggerSource(TI_TRIGGER_PULSER);
	tiEnableTriggerSource();

	/* Enable set specific TS input bits (1-6) */
	tiEnableTSInput( TI_TSINPUT_1 | TI_TSINPUT_2 );

	/* Load the trigger table that associates
	 *  pins 21/22 | 23/24 | 25/26 : trigger1
	 *  pins 29/30 | 31/32 | 33/34 : trigger2
	 */
	tiLoadTriggerTable(0);

	tiSetTriggerHoldoff(1,10,0);
	tiSetTriggerHoldoff(2,10,0);

	/* Set initial number of events per block */
	tiSetBlockLevel(blockLevel);

	/* Set Trigger Buffer Level */
	tiSetBlockBufferLevel(BUFFERLEVEL);

	/* Add Slave */
	tiAddSlave(1);

	/* Init the SD library so we can get status info */
	stat = sdInit(0);	
	if(stat == 0)
	{
		sdSetActiveVmeSlots(0);
		sdStatus(0);
	}
	tiStatus(0);

	printf("TI Initilized\n");
	printf("--------\n");
	printf("rocDownload: etmaster.c Downloaded Executed");
} /* end Download */

/****************************************
 *  PRESTART
 ****************************************/
void
rocPrestart()
{
	/* Set number of events per block */
	tiSetBlockLevel(blockLevel);
	printf("rocPrestart: Block Level set to %d\n",blockLevel);

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

	printf("rocPrestart: etmaster.c Prestart Executed");
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

	/* Get the Current Block Level */
	blockLevel = tiGetCurrentBlockLevel();

	printf("rocGo: Block Level set to %d\n", blockLevel);
#ifdef INTRANDOMPULSER
	/* Enable Random at rate 500kHz/(2^7) = ~3.9kHz */
	tiSetRandomTrigger(1,0xe);
#elif defined (INTFIXEDPULSER)
	/* Enable fixed rate with period (ns) 120 +30*700*(1024^0) = 21.1 us (~47.4 kHz)
	   - Generated 1000 times */
	tiSoftTrig(1,1000,700,0);
#endif
} /* end Go */

/****************************************
 *  END
 ****************************************/
void
rocEnd()
{
	/* Example: How to stop internal pulser trigger */
#ifdef INTRANDOMPULSER
	/* Disable random trigger */
	tiDisableRandomTrigger();
#elif defined (INTFIXEDPULSER)
	/* Disable Fixed Rate trigger */
	tiSoftTrig(1,0,700,0);
#endif
	tiStatus(0);
	printf("rocEnd: Ended after %d blocks\n",tiGetIntCount() );
} /* end rocEnd */

/****************************************
 *  TRIGGER
 ****************************************/
void
rocTrigger(int arg)
{

	static int counter;
	printf("\nTrigger %d Received\n",counter);
	counter++;

	int dCnt;
	const int nwords = 32;
	tiSetOutputPort(1,0,0,0);
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
	printf("\n---------\nPerforming Readout of Fifo Reg...\n---------\n");
	BANKOPEN(1,BT_UI4,blockLevel);
	*dma_dabufp++ = 0xcccc0000;
	*dma_dabufp++ = tiGetIntCount();
	BANKCLOSE;

	BANKOPEN(2,BT_UI4,1);
	*dma_dabufp++ = 0xcebafabc;
	if(nwords<=0) printf("No Scaler data or Error... nwords = %d\n",nwords);
	else
	{
		printf("nwords = %d\n", nwords);
		//Scaler Data is already in a bank structure. Bump the pointer
		int i;
		for(i = 0; i < nwords; i++ )
		{
			*dma_dabufp++ = i*i;
			if(i %4 == 0) printf("\n");
			printf("0x%08x\t", LSWAP(*dma_dabufp));	
			LSWAP(*dma_dabufp);
			dma_dabufp++;
		}
	}
	BANKCLOSE;

	tiSetOutputPort(0,0,0,0);

} /* end rocTrigger */

void
rocCleanup()
{
	printf("%s: Reset all Modules\n", __FUNCTION__);
} /* end rocCleanup */
