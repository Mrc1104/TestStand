/******************************************************************************
 *
 *  flexioLib.c   -  Driver library header file for readout of a TJNAF
 *                   Flexible Input/Output Module using a VxWorks 5.2
 *                   or later based single board computer.
 *
 *  Author: Paul King
 *          University of Maryland / TJNAF G0 Collaboration
 *          March 2001
 *
 *  Revision 1.0 - Initial revision.
 *  2021-jun-25:   Updated to work with 64-bit Linux CPUs.  Using Bryan's crateSharedMem and scalIntLib as examples for the adaptation.
 */

#ifdef VXWORKSPPC
#include "vxWorks.h"
#include "logLib.h"
#include "vxLib.h"
#else
#include "jvme.h"
#endif
#include "stdio.h"
//#include "string.h"
//#include "taskLib.h"
//#include "intLib.h"

/* Include flexIO definitions */
#include "flexioLib.h"

#ifdef VXWORKSPPC
IMPORT  STATUS sysBusToLocalAdrs(int, char *, char **);
#endif

int flexioDebug = FALSE;

volatile struct flexio_struct *flexp;


/******************************************************************************
* flexioInit - Initialize Scale 32 library. Disable/Clear Counters
*
*
* RETURNS: OK, or ERROR if the scaler address is invalid.
*/

int flexioInit (unsigned int addr)
{
  int res, errFlag = 0;
  short rdata;
  unsigned long laddr;

  /* get the FlexIO's address */
  res = vmeBusToLocalAdrs(0x29,(char *)(unsigned long) addr,(char **) &laddr);
  if (res != 0) {
      printf("scale32Init: ERROR in sysBusToLocalAdrs(0x29,0x%x,&laddr) \n",
	     addr);
      return(ERROR);
  } else {
    flexp = (struct flexio_struct *) laddr;
    /* Check if FlexIO Board exists at that address, and send reset */
    res = vmeMemProbe((char *) &(flexp->csr1),2,(char *)&rdata);
    if(res < 0) {
      printf("flexioInit: ERROR: No addressable board at addr=0x%lx\n",
	     (unsigned long)flexp);
      flexp = NULL;
      errFlag=1;
    } else {
      vmeWrite16(&(flexp->csr1), FLEXIO_CSR_RESET);
      if(flexioDebug){
	printf("flexioInit: INFO: flexp->csr1 = 0x%04x \n", vmeRead16(&(flexp->csr1)));
	printf("flexioInit: INFO: flexp->csr2 = 0x%04x \n", vmeRead16(&(flexp->csr2)));    
      }
      printf("Initialized FlexIO at address 0x%lx \n",(unsigned long) flexp);
    }
  }  
    
  if(errFlag > 0) {
    printf("flexioInit: ERROR: Unable to initialize FlexIO \n");
    return(ERROR);
  } else {
    return(OK);
  }
}

/******************************************************************************
 *  flexioReset
 */
void flexioReset(){
  vmeWrite16(&(flexp->csr1), FLEXIO_CSR_RESET);
  vmeWrite16(&(flexp->csr2), FLEXIO_CSR_RESET);
}

/******************************************************************************
 *  flexioPrintStatus
 */
void flexioPrintStatus()
{
  printf("flexioPrintStatus: INFO: flexp->csr1      = 0x%04x\n",vmeRead16(&(flexp->csr1)));
  flexioPrintID(1);
  printf("flexioPrintStatus: INFO: flexp->csr2      = 0x%04x\n",vmeRead16(&(flexp->csr2)));
  flexioPrintID(2);
  printf("flexioPrintStatus: INFO: flexp->data1     = 0x%04x\n",vmeRead16(&(flexp->data1)));
  printf("flexioPrintStatus: INFO: flexp->data2     = 0x%04x\n",vmeRead16(&(flexp->data2)));
  printf("flexioPrintStatus: INFO: flexp->interrupt = 0x%04x\n",
	 vmeRead16(&(flexp->interrupt)));
}

/******************************************************************************
 *  flexioPrintID
 */
void flexioPrintID(int portnum)
{
  int idblock;

  idblock = 0;
  switch (portnum){
  case 1:
    idblock = (vmeRead16(&(flexp->csr1)) & FLEXIO_CSR_ID_MASK)>>FLEXIO_CSR_ID_OFFSET;
    break;
  case 2:
    idblock = (vmeRead16(&(flexp->csr2)) & FLEXIO_CSR_ID_MASK)>>FLEXIO_CSR_ID_OFFSET;    
    break;
  default:
    printf("flexioPrintID: ERROR: port # %d is invalid, must be 1 or 2 \n",
	   portnum);
    return;
    break;
  }
  switch (idblock){
  case FLEXIO_ID_EMPTY:
    printf("flexioPrintID: INFO: port number %d is empty.\n",
	   portnum);
    break;
  case FLEXIO_ID_INPUT:
    printf("flexioPrintID: INFO: port number %d is an input card.\n",
	   portnum);
    break;
  case FLEXIO_ID_OUTPUT:
    printf("flexioPrintID: INFO: port number %d is an output card.\n",
	   portnum);
    break;
  default:
    printf("flexioPrintID: ERROR: port number %d does not have a valid ID.\n",
	   portnum);
    return;
    break;
  }
}

/******************************************************************************
 *  flexioCheckID
 */
int flexioCheckID(int portnum, int porttype)
{
  int idblock;

  idblock = 0;
  switch (portnum){
  case 1:
    if(flexioDebug)
      printf("flexioCheckID: INFO: flexp->csr1 = 0x%04x\n",vmeRead16(&(flexp->csr1)));
    idblock = (vmeRead16(&(flexp->csr1)) & FLEXIO_CSR_ID_MASK)>>FLEXIO_CSR_ID_OFFSET;
    break;
  case 2:
    if(flexioDebug)
      printf("flexioCheckID: INFO: flexp->csr2 = 0x%04x\n",vmeRead16(&(flexp->csr2)));
    idblock = (vmeRead16(&(flexp->csr2)) & FLEXIO_CSR_ID_MASK)>>FLEXIO_CSR_ID_OFFSET;    
    break;
  default:
    printf("flexioCheckID: ERROR: port # %d is invalid, must be 1 or 2 \n",
	   portnum);
    return(ERROR);
    break;
  }

  if(idblock==porttype) {
    return(OK);
  } else {
    return(ERROR);
  }
}

/******************************************************************************
 *  flexioReadData
 */
int flexioReadData(int portnum)
{
  int datablock;

  if(flexp == NULL) {
    printf("flexioReadData: ERROR : Flex IO board not initialized \n");
    return(-1);
  }

  datablock = 0;
  switch (portnum){
  case 1:
    if(flexioDebug)
      printf("flexioReadData: INFO: flexp->data1 = 0x%04x\n",vmeRead16(&(flexp->data1)));
    datablock = vmeRead16(&(flexp->data1));
    if (flexioCheckID(portnum,FLEXIO_ID_INPUT)==OK &&
	flexioIsExtLatch(portnum)==OK) flexioEnableInputLatch(portnum);
    break;
  case 2:
    if(flexioDebug)
      printf("flexioReadData: INFO: flexp->data2 = 0x%04x\n",vmeRead16(&(flexp->data2)));
    datablock = vmeRead16(&(flexp->data2));
    if (flexioCheckID(portnum,FLEXIO_ID_INPUT)==OK &&
	flexioIsExtLatch(portnum)==OK) flexioEnableInputLatch(portnum);
    break;
  default:
    printf("flexioReadData: ERROR: port number %d is invalid, must be 1 or 2 \n",
	   portnum);
    break;
  }

  return(datablock);
}

/******************************************************************************
 *  flexioWriteData
 */
int flexioWriteData(int portnum, int writedata)
{
  int readdata;

  if(flexp == NULL) {
    printf("flexioWriteData: ERROR : Flex IO board not initialized \n");
    return(-1);
  }

  if(flexioCheckID(portnum,FLEXIO_ID_OUTPUT)==ERROR) {
    printf("flexioWriteData: ERROR : Port %d is not an output port.\n",
	   portnum);
    return(-1);
  }
  
  if(flexioDebug)
    printf("flexioWriteData: INFO: Writing 0x%04x to port %d\n",
	   writedata, portnum);
 
  switch (portnum){
  case 1:
    vmeWrite16(&(flexp->data1), writedata);
    break;
  case 2:
    vmeWrite16(&(flexp->data2), writedata);
    break;
  default:
    printf("flexioWriteData: ERROR: port # %d is invalid, must be 1 or 2 \n",
	   portnum);
    break;
  }

  readdata = flexioReadData(portnum);

  return(readdata);
}

/******************************************************************************
 *  flexioWriteMaskCard
 */
int flexioWriteMaskCard(int portnum, int value, int bitpattern)
{
  int retval;
  if (value==0) retval = flexioUnsetDataMask(portnum, bitpattern);
  else          retval = flexioSetDataMask(portnum, bitpattern);
  return retval;
}

/******************************************************************************
 *  flexioSetDataMask
 */
int flexioSetDataMask(int portnum, int bitpattern)
{
  int readdata;
  int writedata;

  if(flexp == NULL) {
    printf("flexioSetDataMask: ERROR : Flex IO board not initialized \n");
    return(-1);
  }

  if(flexioCheckID(portnum,FLEXIO_ID_OUTPUT)==ERROR) {
    printf("flexioSetDataMask: ERROR : Port %d is not an output port.\n",
	   portnum);
    return(-1);
  } else {
    readdata   = flexioReadData(portnum);
    //    writedata  = (readdata | bitpattern) - (readdata & bitpattern);
    writedata  = (readdata | bitpattern);
    readdata   = flexioWriteData(portnum,writedata);
    
    return(readdata);
  }
};

/******************************************************************************
 *  flexioUnsetDataMask
 */
int flexioUnsetDataMask(int portnum, int bitpattern)
{
  int readdata;
  int writedata;

  if(flexp == NULL) {
    printf("flexioUnsetDataMask: ERROR : Flex IO board not initialized \n");
    return(-1);
  }

  if(flexioCheckID(portnum,FLEXIO_ID_OUTPUT)==ERROR) {
    printf("flexioUnsetDataMask: ERROR : Port %d is not an output port.\n",
	   portnum);
    return(-1);
  } else {
    readdata   = flexioReadData(portnum);
    //    writedata  = (readdata | bitpattern) - (readdata & bitpattern);
    writedata   = (readdata | bitpattern);
    writedata  ^= bitpattern;
    readdata    = flexioWriteData(portnum,writedata);
    
    return(readdata);
  }
}

/******************************************************************************
 *  flexioToggleData
 */
int flexioToggleData(int portnum, int bitpattern)
{
  int readdata;
  int writedata;

  if(flexp == NULL) {
    printf("flexioToggleData: ERROR : Flex IO board not initialized \n");
    return(-1);
  }

  if(flexioCheckID(portnum,FLEXIO_ID_OUTPUT)==ERROR) {
    printf("flexioToggleData: ERROR : Port %d is not an output port.\n",
	   portnum);
    return(-1);
  } else {
    readdata   = flexioReadData(portnum);
    //    writedata  = (readdata | bitpattern) - (readdata & bitpattern);
    writedata  = (readdata ^ bitpattern);
    readdata   = flexioWriteData(portnum,writedata);
    
    return(readdata);
  }
}

/******************************************************************************
 *  flexioWriteChan
 */
int flexioWriteChan(int value, int bitposition)
{
  int mask;
  int retval;
  int portnum = 1;

  if(flexp == NULL) {
    printf("flexioWriteChan: ERROR : Flex IO board not initialized \n");
    return(-1);
  }

  if(flexioCheckID(portnum ,FLEXIO_ID_OUTPUT)==ERROR) portnum++;
  if(flexioCheckID(portnum,FLEXIO_ID_OUTPUT)==ERROR) {
    printf("flexioWriteChan: ERROR : Port %d is not an output port.\n",
	   portnum);
    return(-1);
  } else {
    mask = 0;
    if (bitposition>0 && bitposition<=16)  mask = 1<<(bitposition-1);    
    retval = flexioWriteMaskCard(portnum, value, mask);
  }
  return retval;
}



/******************************************************************************
 *  flexioSetOutputMode
 */
int flexioSetOutputMode(int portnum, int outputmode)
{
  if(flexp == NULL) {
    printf("flexioSetOutputMode: ERROR : Flex IO board not initialized \n");
    return(ERROR);
  }
  if(flexioCheckID(portnum,FLEXIO_ID_OUTPUT)==ERROR) {
    printf("flexioSetOutputMode: ERROR : Port %d is not an output port.\n",
	   portnum);
    return(ERROR);
  }
  return(OK);
}



/******************************************************************************
 *  flexioEnableInputLatch
 */
int flexioEnableInputLatch(int portnum)
{
  int localmask;

  if(flexp == NULL) {
    printf("flexioIsExtLatch: ERROR : Flex IO board not initialized \n");
    return(ERROR);
  }
  if(flexioCheckID(portnum,FLEXIO_ID_INPUT)==ERROR) {
    printf("flexioIsExtLatch: ERROR : Port %d is not an input port.\n",
	   portnum);
    return(ERROR);
  }

  localmask = FLEXIO_CSR_IN_STROBE | FLEXIO_CSR_IN_LATCH |
    FLEXIO_CSR_IN_ACT_STR;
  if (flexioSetCSRMask(portnum,localmask)==ERROR){
    return(ERROR);
  } else {
    return( flexioIsExtLatch(portnum) );
  }
}

/******************************************************************************
 *  flexioIsExtLatch
 */
int flexioIsExtLatch(int portnum)
{
  int localmask;

  if(flexp == NULL) {
    printf("flexioIsExtLatch: ERROR : Flex IO board not initialized \n");
    return(ERROR);
  }
  if(flexioCheckID(portnum,FLEXIO_ID_INPUT)==ERROR) {
    printf("flexioIsExtLatch: ERROR : Port %d is not an input port.\n",
	   portnum);
    return(ERROR);
  }

  localmask = FLEXIO_CSR_IN_STROBE | FLEXIO_CSR_IN_LATCH;
  if (flexioCheckCSRMask(portnum,localmask)==ERROR){
    return(ERROR);
  } else {
    return(OK);
  }
}

/******************************************************************************
 *  flexioCheckCSRMask
 */
int flexioCheckCSRMask(int portnum, int csrmask)
{
  int isamatch;

  if(flexp == NULL) {
    printf("flexioCheckCSRMask: ERROR : Flex IO board not initialized \n");
    return(ERROR);
  }

  isamatch = FALSE;
  switch (portnum){
  case 1:
    if ( (vmeRead16(&(flexp->csr1)) & csrmask) == csrmask)  isamatch = TRUE;
    break;
  case 2:
    if ( (vmeRead16(&(flexp->csr2)) & csrmask) == csrmask)  isamatch = TRUE;
    break;
  default:
    printf("flexioCheckCSRMask: ERROR: port # %d is invalid, must be 1 or 2 \n",
	   portnum);
    break;
  }

  if (isamatch==TRUE){
    return(OK);
  } else {
    return(ERROR);
  }
}

/******************************************************************************
 *  flexioSetCSRMask
 */
int flexioSetCSRMask(int portnum, int csrmask)
{
  if(flexp == NULL) {
    printf("flexioSetCSRMask: ERROR : Flex IO board not initialized \n");
    return(ERROR);
  }

  switch (portnum){
  case 1:
    vmeWrite16(&(flexp->csr1), csrmask);
    break;
  case 2:
    vmeWrite16(&(flexp->csr2), csrmask);
    break;
  default:
    printf("flexioSetCSRMask: ERROR: port # %d is invalid, must be 1 or 2 \n",
	   portnum);
    break;
  }

  if (flexioCheckCSRMask(portnum,csrmask)==ERROR){
    return(ERROR);
  } else {
    return(OK);
  }
}


/******************************************************************************
 *  flexio
 */
//STATUS flexio
//{
//}

/******************************************************************************
 */

