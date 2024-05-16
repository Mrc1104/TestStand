#define ROL_NAME__ "FRED"
#define MAX_EVENT_LENGTH 40960
#define MAX_EVENT_POOL   100
/* POLLING_MODE */
#define POLLING___
#define POLLING_MODE
#define TEST_MODE
#define INIT_NAME mrc_test__init
#define INIT_NAME_POLL mrc_test__poll
#include <rol.h>
#include <TEST_source.h>
int blklevel = 1;
int maxdummywords = 200;
int trigBankType = 0xff11;
static void __download()
{
    daLogMsg("INFO","Readout list compiled %s", DAYTIME);
#ifdef POLLING___
   rol->poll = 1;
#endif
    *(rol->async_roc) = 0; /* Normal ROC */
  {  /* begin user */
    daLogMsg("INFO","User Download Executed");

  }  /* end user */
} /*end download */     

static void __prestart()
{
CTRIGINIT;
    *(rol->nevents) = 0;
  {  /* begin user */
unsigned long jj;
    daLogMsg("INFO","Entering User Prestart");

    TEST_INIT;
    CTRIGRSS(TEST,1,usrtrig,usrtrig_done);
    CRTTYPE(1,TEST,1);
  TESTflag = 0;
  TEST_prescale = 10;
    daLogMsg("INFO","User Prestart Executed");

  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
    *(rol->nevents) = 0;
    rol->recNb = 0;
} /*end prestart */     

static void __end()
{
  {  /* begin user */
  TESTflag = 0;
    daLogMsg("INFO","User End Executed");

  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
} /* end end block */

static void __pause()
{
  {  /* begin user */
  TESTflag = 0;
    daLogMsg("INFO","User Pause Executed");

  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
} /*end pause */
static void __go()
{

  {  /* begin user */
    daLogMsg("INFO","Entering User Go");

  TESTflag = 1;
  }  /* end user */
    if (__the_event__) WRITE_EVENT_;
}

void usrtrig(unsigned int EVTYPE,unsigned int EVSOURCE)
{
    int EVENT_LENGTH;
  {  /* begin user */
unsigned long ii, evtnum;
  evtnum = *(rol->nevents);
 CEOPEN(ROCID,BT_BANK,blklevel);
{/* inline c-code */
 
CBOPEN(trigBankType,BT_SEG,blklevel);
for(ii=0;ii<blklevel;ii++) {
   if(trigBankType == 0xff11) {
     *rol->dabufp++ = (EVTYPE<<24)|(0x01<<16)|(3);
   }else{
     *rol->dabufp++ = (EVTYPE<<24)|(0x01<<16)|(1);
   }
   *rol->dabufp++ = (blklevel*(evtnum-1) + (ii+1));
   if(trigBankType == 0xff11) {
      *rol->dabufp++ = 0x12345678;
      *rol->dabufp++ = 0;
   }
}
CBCLOSE;
 
 }/*end inline c-code */
CBOPEN(1,BT_UI4,blklevel);
    CBWRITE32(0xda000011); 
{/* inline c-code */
 
  for(ii=0;ii<maxdummywords;ii++) {
     *rol->dabufp++ = ii;
  }
 
 }/*end inline c-code */
    CBWRITE32(0xda0000ff); 
CBCLOSE;
CECLOSE;
  }  /* end user */
} /*end trigger */

void usrtrig_done()
{
  {  /* begin user */
  }  /* end user */
} /*end done */

void __done()
{
poolEmpty = 0; /* global Done, Buffers have been freed */
  {  /* begin user */
  }  /* end user */
} /*end done */

void __reset () 
{
{/* inline c-code */
 
/* This is a test */
 
 }/*end inline c-code */
} /* end of user codes */

