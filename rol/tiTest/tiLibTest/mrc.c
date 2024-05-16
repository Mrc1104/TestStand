/*
 * File:
 *    tiLibTest.c
 *
 * Description:
 *    Test Vme TI interrupts with GEFANUC Linux Driver
 *    and TI library
 *
 *
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jvme.h"
#include "tiLib.h"
/* #include "remexLib.h" */

DMA_MEM_ID vmeIN,vmeOUT;
extern DMANODE *the_event;
extern unsigned int *dma_dabufp;

extern int tiA32Base;
extern int tiNeedAck;

#define BLOCKLEVEL 9
//#define DO_READOUT

/* Interrupt Service routine */
void
mrc_interrupt(int arg)
{
	printf("Trigger #: %d detected\n",tiGetIntCount());
	
	int timeout = 0;
	int tibready = tiBReady();
	unsigned int tiIntCount = tiGetIntCount();
	GETEVENT(vmeIN,tiIntCount);

	printf("Blocks ready to be readout = %d\n", tibready);
	if(tibready==ERROR)
	{
		printf("%s: ERROR: tiIntPoll returned ERROR.\n",__FUNCTION__);
		return;
	}
	if(tibready==0 && timeout<100)
	{
		printf("NOT READY!\n");
		tibready=tiBReady();
		timeout++;
	}
//	int dCnt = tiReadTriggerBlock(dma_dabufp);
	int dCnt = tiReadBlock(dma_dabufp,5*BLOCKLEVEL+3+4,1);
	printf("dCnt = %d\n", dCnt);
	printf("dma_dabufp = %d\n", dma_dabufp);
	if(dCnt <= 0){
		printf("NO data or ERROR. dCnt = %d\n",dCnt);	
	}
	else{
		dma_dabufp += dCnt;
	}

	PUTEVENT(vmeOUT);
	int length = ( ((int)(dma_dabufp) - (int)(&the_event->length)) ) - 4;
	int size = the_event->part->size - sizeof(DMANODE);
	printf("length = %d\n", length);
	printf("size = %d\n", size);

	DMANODE* outEvent = dmaPGetItem(vmeOUT);
	int len = outEvent->length;
	int idata;
	for(idata = 0; idata < len; idata++){
		if( idata%5==0) printf("\n\t");
		printf("0x%08x ", (unsigned int)LSWAP(outEvent->data[idata]));	
	}
	printf("\n\n");
	dmaPFreeItem(outEvent);

			
}


int
main(int argc, char *argv[]) {

	int stat;

	printf("\nmrc testing grounds\n");
	printf("----------------------------\n");

	/* remexSetCmsgServer("dafarm28"); */
	/* remexInit(NULL,1); */

	printf("Size of DMANODE    = %d (0x%x)\n",sizeof(DMANODE),sizeof(DMANODE));
	printf("Size of DMA_MEM_ID = %d (0x%x)\n",sizeof(DMA_MEM_ID),sizeof(DMA_MEM_ID));

	vmeOpenDefaultWindows();

	/* Setup Address and data modes for DMA transfers
	 *
	 *  vmeDmaConfig(addrType, dataType, sstMode);
	 *
	 *  addrType = 0 (A16)    1 (A24)    2 (A32)
	 *  dataType = 0 (D16)    1 (D32)    2 (BLK32) 3 (MBLK) 4 (2eVME) 5 (2eSST)
	 *  sstMode  = 0 (SST160) 1 (SST267) 2 (SST320)
	 */
	vmeDmaConfig(2,5,1);

	/* INIT dmaPList */
	dmaPFreeAll();
	vmeIN  = dmaPCreate("vmeIN",1024,4,0);
	vmeOUT = dmaPCreate("vmeOUT",0,0,0);

	dmaPStatsAll();
	dmaPReInitAll();

	tiA32Base=0x09000000;
	tiSetFiberLatencyOffset_preInit(0x20);
	tiInit(0,TI_READOUT_EXT_POLL,TI_INIT_SKIP_FIRMWARE_CHECK);
	tiCheckAddresses();

	tiSetEvTypeScalers(1);


	tiSetSyncEventInterval(0);
	tiSetEventFormat(3);

	char mySN[20];
	printf("0x%08x\n",tiGetSerialNumber((char **)&mySN));
	printf("mySN = %s\n",mySN);

	/* user defined tiTrigger Table
	 * TS# 1 & 6 generates Trigger 1 (Physics)
	 * No Trigger 2 (Playback Trigger)
	 * No SyncEvent
	 */

	unsigned int tiTable_coinc_test[16] = { /* Ts# 1 & 6 generate Trigger 1 (Physics) */
		0x03024100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
		0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
		0x2321a160, 0x27262524, 0x2b2a2928, 0x2f2e2d2c,
		0x33323130, 0x37363534, 0x3b3a3938, 0x3f3e3d3c,
	};

	
	tiTriggerTableConfig(tiTable_coinc_test);	
	tiSetTriggerHoldoff(2,4,0);

	tiSetBlockLevel(BLOCKLEVEL);
	tiSetTriggerWindow(1);

	stat = tiIntConnect(TI_INT_VEC, mrc_interrupt, 0);
	if (stat != OK)
	{
		printf("ERROR: tiIntConnect failed \n");
		goto CLOSE;
	}
	else
	{
		printf("INFO: Attached TI Interrupt\n");
	}

	tiSetTriggerSource(TI_TRIGGER_TSINPUTS);
	tiDisableTSInput(0x3f);
	tiEnableTSInput(0x21); // TS 1,6

	tiSetFPInputReadout(1);

	tiSetBusySource(TI_BUSY_LOOPBACK,1);
	tiSetBlockBufferLevel(1);

	/*   tiSetFiberDelay(1,2); */
	/*   tiSetSyncDelayWidth(1,0x3f,1); */

	tiSetBlockLimit(9);
	tiSetScalerMode(1, 1);

	tiPrintTriggerTable(1);

	tiClockReset();
	taskDelay(1);
	tiTrigLinkReset();
	taskDelay(1);
	tiEnableVXSSignals();

	tiSyncReset(1);

	printf("Hit enter to start triggers\n");
	getchar();

	tiIntEnable(0);

	printf("Hit any key to Disable TID and exit.\n");
	getchar();

	tiIntDisable();
	tiIntDisconnect();

	tiPrintEvTypeScalers();

CLOSE:

	dmaPFreeAll();
	vmeCloseDefaultWindows();

	exit(0);
}

/*
   Local Variables:
   compile-command: "make -k -B tiLibTest"
End:
*/
