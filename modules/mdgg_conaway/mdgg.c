/* mdgg .c file */


#include "mdgg.h"


int Nmdgg;
struct mdgg_register_struct* mdggp[5];
struct mdgg_register_struct missingmdgg;


/* initialization */

STATUS mdggInit (UINT32 addr, UINT32 addr_inc, int nmdggs)
{
  int ii, res, rdata, errFlag = 0;
  unsigned long laddr;

  /* Check for valid address */
  if(addr==0) {
    printf("Init: ERROR: Must specify a local VME-based (A24) address for MDGG 0\n");
    return(ERROR);
  }else{
    if((addr_inc==0)||(nmdggs==0))
      nmdggs = 1; /* assume only one MDGG to initialize */

    Nmdgg = 0;


    /* get the MDGG's address */
    res = vmeBusToLocalAdrs(0x39,(char *)addr,(char **)&laddr);
    if (res != 0) {
      printf("mdggInit: ERROR in vmeBusToLocalAdrs(0x39,0x%x,&laddr)\n",addr);
      return(ERROR);
    } else {
      for (ii=0;ii<nmdggs;ii++) {
        Nmdgg++;
        mdggp[ii] = (struct mdgg_register_struct *)(laddr + ii*addr_inc);
        /* Check if Board exists at that address */
	res = vmeMemProbe((char *) mdggp[ii],4,(char *)&rdata);
	if(res < 0) {
          printf("mdggInit: ERROR: No addressable board at addr=0x%x\n",
                 (UINT32) mdggp[ii]);
          /* If there is no addressable board here, connect this to the "missingmdgg", and keep going. */
          mdggp[ii] = &missingmdgg;
          errFlag++;
        } else {
          printf("mdggInit: Initialized MDGG ID %d at address 0x%08x with default parameters\n",
                 ii, (UINT32) mdggp[ii]);

	}
      }
    }
  }


  if(Nmdgg <=0 || Nmdgg == errFlag){

    return(ERROR);
  } else if (errFlag ==0) {
    printf("mdggInit: %d MDGG(s) successfully initialized\n",
           Nmdgg);
  } else {
    printf("mdggInit: %d MDGG(s) successfully initialized; %d MDGG(s) had initalization errors\n",
           Nmdgg-errFlag, errFlag);
  }
  return(OK);
}


/* setDefaults */

void setDefaults ()
{
  vmeWrite32(&(mdggp[0]->global_register), 0);
  vmeWrite32(&(mdggp[0]->auxillary_register), 0);
  vmeWrite32(&(mdggp[0]->FGG_configuration), 0);
  vmeWrite32(&(mdggp[0]->scaler_configuration), 0);
  vmeWrite32(&(mdggp[0]->FGG_input_selector_A), 0x03020100);
  vmeWrite32(&(mdggp[0]->FGG_input_selector_B), 0x07060504);
  vmeWrite32(&(mdggp[0]->NIM_output_selector_A), 0x03020100);
  vmeWrite32(&(mdggp[0]->NIM_output_selector_B), 0x07060504);
  vmeWrite32(&(mdggp[0]->scaler_input_selector_A), 0x03020100);
  vmeWrite32(&(mdggp[0]->scaler_input_selector_B), 0x07060504);
  vmeWrite32(&(mdggp[0]->combination_gate_mask_A), 0);
  vmeWrite32(&(mdggp[0]->combination_gate_mask_B), 0);
}


/* assignMask */

int assignMask (UINT32* reg, UINT32 mask, unsigned int offset, UINT32 value)
{
  UINT32 data;
  UINT32 lmask;
  data = vmeRead32(reg);
  lmask = ~(mask<<(offset));
  data &= lmask;
  data += (mask&value)<<(offset);
  vmeWrite32(reg, data);
  return 0;
}


/* getFirmware */

unsigned long getFirmware ()
{
  return vmeRead32(&(mdggp[0]->firmware_ID));
}


/* setGlobalRegister_FGGVeto */

int setGlobalRegister_FGGVeto (UINT32 value)
{
  return assignMask(&(mdggp[0]->global_register), 0x1f, 0, value);
}

/* setGlobalRegister_SclrGa */

int setGlobalRegister_SclrGa (UINT32 value)
{
  return assignMask(&(mdggp[0]->global_register), 0x1f, 8, value);
}


/* setGlobalRegister_SclrLatch */

int setGlobalRegister_SclrLatch (UINT32 value)
{
  return assignMask(&(mdggp[0]->global_register), 0x1f, 16, value);
}


/* setGlobalRegister_MReset */

int setGlobalRegister_MReset (UINT32 value)
{
  return assignMask(&(mdggp[0]->global_register), 0x1f, 24, value);
}


/* setAuxillaryRegister_FGGMResetMask */

int setAuxillaryRegister_FGGMResetMask (UINT32 value)
{
  return assignMask(&(mdggp[0]->auxillary_register), 0xff, 0, value);
}


/* setAuxillaryRegister_SelCRegGa */

int setAuxillaryRegister_SelCRegGa (UINT32 value)
{
  return assignMask(&(mdggp[0]->auxillary_register), 0x1f, 8, value);
}


/* setAuxillaryRegister_CRegMResetmask */

int setAuxillaryRegister_CRegResetMask (UINT32 value)
{
  return assignMask(&(mdggp[0]->auxillary_register), 0x1, 13, value);
}


/* setDelay */

int setDelay(int chan, unsigned long delay)
{
  if (chan < 1 || chan > 8)
    {
      printf("\nInvalid channel number (1-8)\n");
      return 0;
    }
  chan--;
  vmeWrite32(&((mdggp[0]->channel[chan]).delay_FGG), delay);
  return 0;
}


/* setGate */

int setGate(int chan, unsigned long gate)
{
  if (chan < 1 || chan > 8)
    {
      printf ("\nInvalid channel number (1-8)\n");
      return 0;
    }
  chan--;
  vmeWrite32(&((mdggp[0]->channel[chan]).gate_FGG), gate);
  return 0;
}


/* setActionRegister_ResFGG */

int setActionRegister_ResFGG (UINT32 value)
{
  return assignMask(&(mdggp[0]->action_register), 0xff, 0, value);
}


/* setActionRegister_ResSclr */

int setActionRegister_ResSclr (UINT32 value)
{
  return assignMask(&(mdggp[0]->action_register), 0xff, 8, value);
}


/* setActionRegister_TrigFGG */

int setActionRegister_TrigFGG (UINT32 value)
{
  return assignMask(&(mdggp[0]->action_register), 0xff, 16, value);
}


/* setActionRegister_ResCREG */

int setActionRegister_ResCREG (UINT32 value)
{
  return assignMask(&(mdggp[0]->action_register), 0x1, 24, value);
}


/* setFGGConfiguration */

int setFGGConfiguration(int chan, enum mdgg_fgg_configuration value)
{
  chan--;
  return  assignMask(&(mdggp[0]->FGG_configuration), 0xf, chan*4, value);
}


/* setScalerConfiguration */

int setScalerConfiguration(int chan, enum mdgg_scaler_configuration value)
{
  chan--;
  return assignMask(&(mdggp[0]->scaler_configuration), 0xf, chan*4, value);
}


/* setFGGInputSelector */

int setFGGInputSelector (int chan, unsigned long value)
{
  UINT32* reg;
  int offset;
  if (chan <= 4 && chan > 0) {
    reg = &(mdggp[0]->FGG_input_selector_A);
    offset = 8*(chan-1);
  } else if (chan <= 8 && chan > 4) {
    reg = &(mdggp[0]->FGG_input_selector_B);
    offset = 8*(chan-5);
  } else {
    printf ("\nInvalid channel number (1-8)\n");
    return 0;
  }
  return assignMask(reg, 0x1f, offset, value);
}


/* setNIMOutputSelector */

int setNIMOutputSelector (int chan, unsigned long value)
{
  UINT32* reg;
  int ret;
  int offset;
  if (chan <= 4 && chan > 0) {
    reg = &(mdggp[0]->NIM_output_selector_A);
    offset = 8*(chan-1);
  } else if (chan <= 8 && chan > 4) {
    reg = &(mdggp[0]->NIM_output_selector_B);
    offset = 8*(chan-5);
  } else {
    printf ("\nInvalid channel number (1-8)\n");
    return 0;
  }
  ret = assignMask(reg, 0x1f, offset, value);

  return ret;
}


/* setFGGStopSelector */

int setFGGStopSelector (int chan, unsigned long value)
{
  UINT32* reg;
  int offset;
  if (chan <= 4 && chan > 0) {
    reg = &(mdggp[0]->FGG_stop_selector_A);
    offset = 8*(chan-1);
  } else if (chan <= 8 && chan > 4) {
    reg = &(mdggp[0]->FGG_stop_selector_B);
    offset = 8*(chan-5);
  } else {
    printf ("\nInvalid channel number (1-8)\n");
    return 0;
  }
  return assignMask(reg, 0x1f, offset, value);
}


/* setScalerInputSelector */

int setScalerInputSelector (int chan, unsigned long value)
{
  UINT32* reg;
  int offset;
  if (chan <= 4 && chan > 0) {
    reg = &(mdggp[0]->scaler_input_selector_A);
    offset = 8*(chan-1);
  } else if (chan <= 8 && chan > 4) {
    reg = &(mdggp[0]->scaler_input_selector_B);
    offset = 8*(chan-5);
  } else {
    printf ("\nInvalid channel number (1-8)\n");
    return 0;
  }
  return assignMask(reg, 0x1f, offset, value);
}


/* setLogicalMask */

int setLogicalMask (int chan, unsigned long value)
{
  UINT32* reg;
  int offset;
  if (chan <= 4 && chan > 0) {
    reg = &(mdggp[0]->combination_gate_mask_A);
    offset = 8*(chan-1);
  } else if (chan <= 8 && chan > 4) {
    reg = &(mdggp[0]->combination_gate_mask_B);
    offset = 8*(chan-5);
  } else {
    printf ("\nInvalid channel number (1-8)\n");
    return 0;
  }
  return assignMask(reg, 0xff, offset, value);
}


/* getScalerData */

unsigned long getScalerData (int chan)
{
  return vmeRead32(&((mdggp[0]->channel1[chan-1]).scaler_data));
}

/* getScalerMultiplicity */

unsigned long getScalerMultiplicity (int chan)
{
  return vmeRead32(&((mdggp[0]->channel2[chan-1]).scaler_latch_multiplicity));
}

/* getCoincidenceRegister */

unsigned long getCoincidenceRegister()
{
  return vmeRead32(&(mdggp[0]->coincidence_register));
}


/* mdggPrintStatus */

int mdggPrintStatus (int chan)
{
  int firm_ID, glob_reg, aux_reg, gate, delay, act_reg, FGG_conf, sca_conf, input_A, input_B;
  int output_A, output_B, stop_A, stop_B, sca_A, sca_B, mask_A, mask_B, sca_data, sca_mul, c_reg;
  firm_ID=vmeRead32(&(mdggp[0]->firmware_ID));
  glob_reg=vmeRead32(&(mdggp[0]->global_register));
  aux_reg=vmeRead32(&(mdggp[0]->auxillary_register));
  gate=vmeRead32(&((mdggp[0]->channel[chan-1]).gate_FGG));
  delay=vmeRead32(&((mdggp[0]->channel[chan-1]).delay_FGG));
  act_reg=vmeRead32(&(mdggp[0]->action_register));
  FGG_conf=vmeRead32(&(mdggp[0]->FGG_configuration));
  sca_conf=vmeRead32(&(mdggp[0]->scaler_configuration));
  input_A=vmeRead32(&(mdggp[0]->FGG_input_selector_A));
  input_B=vmeRead32(&(mdggp[0]->FGG_input_selector_B));
  output_A=vmeRead32(&(mdggp[0]->NIM_output_selector_A));
  output_B=vmeRead32(&(mdggp[0]->NIM_output_selector_B));
  stop_A=vmeRead32(&(mdggp[0]->FGG_stop_selector_A));
  stop_B=vmeRead32(&(mdggp[0]->FGG_stop_selector_B));
  sca_A=vmeRead32(&(mdggp[0]->scaler_input_selector_A));
  sca_B=vmeRead32(&(mdggp[0]->scaler_input_selector_B));
  mask_A=vmeRead32(&(mdggp[0]->combination_gate_mask_A));
  mask_B=vmeRead32(&(mdggp[0]->combination_gate_mask_B));
  sca_data=vmeRead32(&((mdggp[0]->channel1[chan-1]).scaler_data));
  sca_mul=vmeRead32(&((mdggp[0]->channel2[chan-1]).scaler_latch_multiplicity));
  c_reg=vmeRead32(&(mdggp[0]->coincidence_register));
  float gns, dns, freq;
  gns = gate*8;
  dns = delay*8;
  freq = 1000/(gns + dns);
  printf("\n----------------------------------------------------------------------------------------\n");
  printf("\n Firmware ID:0x%08x, Global Register:0x%08x, Auxillary Register: 0x%08x \n", firm_ID, glob_reg, aux_reg);
  printf("\n Gate%d:0x%08x(%f ns), Delay%d:0x%08x(%f ns), Frequency:%f MHz \n", chan, gate, gns, chan, delay, dns, freq);
  printf("\n Action Register:0x%08x, FGG Config:0x%08x, Scaler Config:0x%08x  \n", act_reg, FGG_conf, sca_conf);
  printf("\n FGG Input Selector A:0x%08x, FGG Input Selector B:0x%08x  \n", input_A, input_B);
  printf("\n NIM Output Selector A:0x%08x, NIM Output Selector B:0x%08x  \n", output_A, output_B);
  printf("\n FGG Stop Selector A:0x%08x, FGG Stop Selector B:0x%08x  \n", stop_A, stop_B);
  printf("\n Scaler Input Selector A:0x%08x, Scaler Input Selector B:0x%08x  \n", sca_A, sca_B);
  printf("\n Combination Mask A:0x%08x, Combination Mask B:0x%08x  \n", mask_A, mask_B);
  printf("\n Scaler Data%d:0x%08x, Scaler Latch Multiplicity%d:0x%08x, Coincidence Register: 0x%08x  \n", chan, sca_data, chan, sca_mul, c_reg);
  printf("\n----------------------------------------------------------------------------------------\n");
  return 0;
}

