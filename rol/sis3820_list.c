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
#define MAX_EVENT_LENGTH 1024*64 /* size in bytes */
/* Define TI Type */
#define TI_MASTER
/* External trigger source (e.g. front panel ECL input), POLL for available data */
#define TI_READOUT TI_READOUT_EXT_POLL
/* TI VME address, or 0 for Auto Initialize (search for TI by slot) */
#define TO_ADDR 0
/* Measured longest fiber length in systemt */
#define FIBER_LATENCY_OFFSET 0x48
/* Define intiial blocklevel and buffering level */
#define BLOCKLEVEL  1
#define BUFFERLEVEL 3

/****************************
 *    SIS3820 Specifics     *
 ***************************/
#define BASE_ADDRESS 0x09000000
#define NUM_MODULES  1
#define MODULE_ID    0
#define ENABLE       1
#define DISABLE      0
#define N_CHAN       32


/* Headers */
#include "dmaBankTools.h"   /* Macros for handling CODA banks            */
#include "tiprimary_list.c" /* Source required for CODA ROL using the TI */
#include "sdLib.h"
#include "sis3820Lib.h"     /* SIS3820 Library                           */


/* Trigger Table */
unsigned int usrTable[16] = { 
	/* TS# 1,2,3,4,5,6      generate Trigger 1 (Physics) */
	/* TS# 1&6, 1&2, 1&3, 1&4, 1&5 generate Trigger 2 (Physics) */
	0x83424100, 0x07068544, 0x0b0a8948, 0x0f0e0d0c,
	0x13129150, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
	0x2322a160, 0x27262524, 0x2b2a2928, 0x2f2e2d2c,
	0x33323130, 0x37363534, 0x3b3a3938, 0x3f3e3d3c,
};

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

	tiSetTriggerSource(TI_TRIGGER_TSINPUTS);

	/* Enable Specific TS input bits (1-6) */
	tiDisableTSInput(0x3f);
	tiTriggerTableConfig(usrTable);
	tiPrintTriggerTable(1);

	tiSetTriggerHoldoff(1,10,0);
	tiSetTriggerWindow(1e3);

	/* Set initial number of events per block */
	tiSetBlockLevel(blockLevel);

	/* Set Trigger Buffer Level */
	tiSetBlockBufferLevel(blockLevel);

	/* Init the SD library so we can get status info */
	stat = sdInit(0);	
	if(stat == 0)
	{
		sdSetActiveVmeSlots(0);
		sdStatus(0);
	}
	tiStatus(0);
	printf("TI Initilized\n");

	/******************/
	/*  SIS3820 Setup */
	/******************/

	/* Initilize the library */
	sis3820Init(BASE_ADDRESS, 0, 1, 0);	 
	sis3820CheckAddresses();
	sis3820Config(MODULE_ID,3);
	sis3820ControlEnable(MODULE_ID, 1, 0, 0, 1);

	/* Set Operational Mode */
	sis3820SetOperationMode(MODULE_ID, 2); // MCS Mode 
	sis3820SetInputMode(MODULE_ID, 3, 0);  // I1-> external LNE/clockshadow, I2->extern userbit 1, I3->extern userbit 2, I4->inhibit Counting
	sis3820SetOutputMode(MODULE_ID, 1, 0); // O5->Scalar, O6->Enabled, O7->50MHz, 08->User Output (led) 
	sis3820SetSDRAMMode(MODULE_ID, 0);     // FIFO Emulation

	/* Enable Sources */
	sis3820Enable(MODULE_ID);
	sis3820SetArmEnableSource(MODULE_ID, 0); // Enable signal is from LNE Front Panel Control signal

	/* Add Prescalers */
	sis3820SetLNEPrescaleFactor(MODULE_ID, 0);

	/* Set Threshold */
	sis3820SetFifoWordCountThreshold(MODULE_ID,0xffffffff);

	/* Set Veto Mask (Prohibits the inhibit signal for the selected channels) */
	sis3820SetVetoInhibitMask(MODULE_ID, 0x00);

	/* Print Status */
	sis3820Status(MODULE_ID,1);

	/* Set IRQ */
	sis3820SetIRQSource(MODULE_ID, S3820_IRQ_SOURCE_LNE,              ENABLE );
	sis3820SetIRQSource(MODULE_ID, S3820_IRQ_SOURCE_FIFO_THR,         ENABLE );
	sis3820SetIRQSource(MODULE_ID, S3820_IRQ_SOURCE_ACQ_COMPLETE,     DISABLE);
	sis3820SetIRQSource(MODULE_ID, S3820_IRQ_SOURCE_OVERFLOW,         ENABLE );
	sis3820SetIRQSource(MODULE_ID, S3820_IRQ_SOURCE_FIFO_ALMOST_FULL, ENABLE );
	
	/* Set Acquisition */
	sis3820SetAcquisitionPreset(MODULE_ID, 0x00);

	/* Set Data Format */
	sis3820SetNonClearingMode(MODULE_ID, 1); // Store to shadow register or copied to SDRAM/FIFO
	sis3820SetDataFormat(MODULE_ID, S3820_OP_MODE_DATA_FORMAT_32);
	// sis3820SetDataFormat(MODULE_ID, 0);

	printf("TI Initilized\n");
	printf("--------\n");
	printf("rocDownload: sis3820_list.c Downloaded Executed");
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

	printf("rocPrestart: sis3820_list.c Prestart Executed");
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
	/* Enable TS inputs */
	tiEnableTSInput(TI_TSINPUT_1 | TI_TSINPUT_2 | TI_TSINPUT_3 | TI_TSINPUT_4 | TI_TSINPUT_5 | TI_TSINPUT_6);
	/* Enable Scaler Inputs */
	sis3820SetLNESource(MODULE_ID, 1); // LNE source is from front panel

	printf("rocGo: Block Level set to %d\n", blockLevel);
} /* end Go */

/****************************************
 *  END
 ****************************************/
void
rocEnd()
{
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
	int nwords;
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
	BANKOPEN(5,BT_UI4,1);
	*dma_dabufp++ = 0xcebafabc;
	nwords = sis3820CounterRead(MODULE_ID,0, dma_dabufp, 0);
	if(nwords<=0) printf("No Scaler data or Error... nwords = %d\n",nwords);
	else
	{
		printf("nwords = %d\n", nwords);
		//Scaler Data is already in a bank structure. Bump the pointer
		int i;
		for(i = 0; i < nwords; i++ )
		{
			if(i %4 == 0) printf("\n");
			printf("0x%08x\t", LSWAP(*dma_dabufp));	
			LSWAP(*dma_dabufp);
			dma_dabufp++;
		}
	}
	BANKCLOSE;
	BANKOPEN(6,BT_UI4,1);
	int ii;
	int maxdummywords=25; 
  	for(ii=0;ii<maxdummywords;ii++) {
     		*dma_dabufp = ii;
		dma_dabufp++;
	}
	BANKCLOSE;

	tiSetOutputPort(0,0,0,0);

} /* end rocTrigger */

void
rocCleanup()
{
	printf("%s: Reset all Modules\n", __FUNCTION__);
} /* end rocCleanup */
