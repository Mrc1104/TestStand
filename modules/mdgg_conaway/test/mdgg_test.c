#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <jvme.h>
#include "mdgg.h"

#define mdgg_addr 0x100000

int main(int argc, char **argv)
{

	/* Open the VME interface */
	vmeSetQuietFlag(1);
	vmeOpenDefaultWindows();


	/* initialization */
	mdggInit(mdgg_addr, 0, 1);
	setDefaults();

	/* global register, auxillary register, and action register */
	setActionRegister_ResFGG(0xff);  

	setGlobalRegister_SclrGa(12);
/*
	// setGate and setDelay 
	setGate(1,500);
	setDelay(1,2500);
	
	// setGate and setDelay 
	setGate(2,500);
	setDelay(2,3000);
*/
	int one_sec = 125000000;
	/* setGate and setDelay */
	setGate(1,one_sec/1000);
	setDelay(1,one_sec/100);
	//setGate(1,1);
	//setDelay(1,1);
	
	/* setGate and setDelay */
//	setGate(2,one_sec/100);
//	setDelay(2,one_sec/100);
	setGate(2,2);
	setDelay(2,1);
	/* setGate and setDelay */
	setGate(3,one_sec/2);
	setDelay(3,one_sec/2);

	

	/* FGG and scaler configuration */
	setFGGConfiguration(1, 3);
	setFGGConfiguration(2, 3);
	setFGGConfiguration(3, 3);

	
	// FGG will act as a 1/n prescaler
	// How to set n ???
//	setFGGConfiguration(3, 5);

	/* FGG Input channels */
	setFGGInputSelector(3,0);
	

	/* NIM output channels */


	/* FGG stop selectors, scaler input selectors, masks */

	/* print status */
	sleep(5);
	mdggPrintStatus(1);
	mdggPrintStatus(2);
	mdggPrintStatus(3);


	/* Close the VME interface */
	vmeCloseDefaultWindows();


	return 0;

}
