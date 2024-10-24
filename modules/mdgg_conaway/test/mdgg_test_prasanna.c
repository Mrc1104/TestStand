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
 
  /* setGate and setDelay */
  setGate(1,6250);
  setDelay(1,125000);
  
  setGate(2,1250);
  setDelay(2,2500);
  
  setGate(3, 18);
  setDelay(3, 18);

  setGate(4,1024);
  setDelay(4,2048);
  /* FGG and scaler configuration */
  setFGGConfiguration(1, 3);
  setFGGConfiguration(2, 3);
  setFGGConfiguration(3, 3);
  setFGGConfiguration(4, 2);

  setScalerConfiguration(5, 1);
  setScalerConfiguration(6, 1);

  /* FGG Input channels */


  /* NIM output channels */
  

  /* FGG stop selectors, scaler input selectors, masks */
  setScalerInputSelector(5, 8);
  setScalerInputSelector(6, 10);

  setActionRegister_ResSclr(0xff);
  setActionRegister_TrigFGG(8);
    
  /* print status */
  mdggPrintStatus(4);
  printf("I am sleeeping now...Z...Z...Z... \n");
  sleep(5);
  printf("I woke up!");
  mdggPrintStatus(4);

  /* Close the VME interface */
  vmeCloseDefaultWindows();
  

  return 0;

}
