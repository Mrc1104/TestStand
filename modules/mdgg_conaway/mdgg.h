/* mdgg header file */

#include <jvme.h>
#include <unistd.h>
#define UINT8 unsigned char


enum mdgg_fgg_configuration {

  mdgg_fgg_off=0,
  mdgg_dgg=1,
  mdgg_srg=2,
  mdgg_pg=3,
  mdgg_rdgg=4,
  mdgg_psg=5,
  mdgg_cpsg=6

} enum_test;


enum mdgg_scaler_configuration {

  mdgg_scaler_off=0,
  mdgg_gated_scaler=1,
  mdgg_latched_scaler=2,
  mdgg_gated_latched_scaler=3

} enum_test1;



STATUS mdggInit(UINT32 addr, UINT32 addr_inc, int nmdggs);
int assignMask (UINT32* reg, UINT32 mask, unsigned int offset, UINT32 value);
unsigned long getFirmware ();
int setGlobalRegister_FGGVeto (UINT32 value);
int setGlobalRegister_SclrGa (UINT32 value);
int setGlobalRegister_SclrLatch (UINT32 value);
int setGlobalRegister_MReset (UINT32 value);
int setAuxillaryRegister_FGGMResetMask (UINT32 value);
int setAuxillaryRegister_SelCRegGa (UINT32 value);
int setAuxillaryRegister_CRegResetMask (UINT32 value);
int setDelay(int chan, unsigned long delay);
int setGate(int chan, unsigned long gate);
int setActionRegister_ResFGG (UINT32 value);
int setActionRegister_ResSclr (UINT32 value);
int setActionRegister_TrigFGG (UINT32 value);
int setActionRegister_ResCREG (UINT32 value);
int setFGGConfiguration(int chan, enum mdgg_fgg_configuration value);
int setScalerConfiguration(int chan, enum mdgg_scaler_configuration value);
int setFGGInputSelector (int chan, unsigned long value);
int setNIMOutputSelector (int chan, unsigned long value);
int setFGGStopSelector (int chan, unsigned long value);
int setScalerInputSelector (int chan, unsigned long value);
int setLogicalMask (int chan, unsigned long value);
unsigned long getScalerData ();
unsigned long getScalerMultiplicity ();
unsigned long getCoincidenceRegister();
int mdggPrintStatus (int chan);
void setDefaults ();


typedef struct mdgg_channel_struct{

  UINT32 delay_FGG;
  UINT32 gate_FGG;

} mdgg_channel_test;


typedef struct mdgg_channel_struct_1{

  UINT32 scaler_data;

} mdgg_channel_test_1;


typedef struct mdgg_channel_struct_2{

  UINT32 scaler_latch_multiplicity;

} mdgg_channel_test_2;


typedef struct mdgg_register_struct{

  UINT32 firmware_ID;             /* 0x000 */
  UINT32 global_register;         /* 0x004 */
  UINT32 auxillary_register;      /* 0x008 */

  UINT32 dummy[13];               /* 0x00C to 0x03C */

  struct mdgg_channel_struct channel[8];  /* 0x040 to 0x07c */

  UINT32 action_register;         /* 0x080 */
  UINT32 FGG_configuration;       /* 0x084 */
  UINT32 scaler_configuration;    /* 0x088 */
  UINT32 FGG_input_selector_A;    /* 0x08C */
  UINT32 FGG_input_selector_B;    /* 0x090 */
  UINT32 NIM_output_selector_A;   /* 0x094 */
  UINT32 NIM_output_selector_B;   /* 0x098 */
  UINT32 FGG_stop_selector_A;     /* 0x09C */
  UINT32 FGG_stop_selector_B;     /* 0x0A0 */
  UINT32 scaler_input_selector_A; /* 0x0A4 */
  UINT32 scaler_input_selector_B; /* 0x0A8 */
  UINT32 combination_gate_mask_A; /* 0x0AC */
  UINT32 combination_gate_mask_B; /* 0x0B0 */

  UINT32 dummy1[19];              /* 0x0B4 to 0x0fc */

  struct mdgg_channel_struct_1 channel1[8]; /* 0x100 to 0x11C */
  struct mdgg_channel_struct_2 channel2[8]; /* 0x120 to 0x13C */
 
  UINT32 coincidence_register;    /* 0x140 */

} mdgg_test;


