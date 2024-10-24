/*
 * File:
 *    gefcmn_vme_tempe.h
 *
 * Description:
 *    This is a common header file for the tempe driver.
 *
 * Copyright:
 *    Copyright 2007-2011 GE Intelligent Platforms Embedded Systems, Inc.
 *
 * License:
 *    This file is proprietary to GE Intelligent Platforms Embedded Systems, Inc.
 */
/*
 * $Date$
 * $Rev$
 */

#ifndef __GEFCMN_VME_TEMPE_H
#define __GEFCMN_VME_TEMPE_H

#define VME_SLAVE_WINDOWS   8
#define VME_MASTER_WINDOWS  8

/* 
  Tundra Tempe Register Layout - CRG - Combined Register Group
  Range        Bytes   Description
  0x000-0x0FF    256   PCFS - PCI/X Configuration Space Registers
  0x100-0x5FF   1280   LCSR - Local Control and Status Registers
  0x600-0x61F     32   GCSR - Global Control and Status Registers
  0x620-0xBFF   1504   Reserved
  0xC00-0xFFF   1024   CSR  - Control and Status Registers
*/
#define TEMPE_CRG_SIZE		4096  /* Combined Register Group (CRG) 4KByte */

/* PCFS - Byte offsets into the Tundra Tempe chip for the registers */
#define TEMPE_PCI_ID        (0x000)   /* PCI config space ID register */
#define TEMPE_PCI_CSR       (0x004)   /* PCI config space control and status */
#define TEMPE_PCI_CLASS     (0x008)   /* PCI config class register */
#define TEMPE_PCI_MISC0     (0x00C)   /* PCI config miscellaneous 0 regster */
#define TEMPE_PCI_MBARL     (0x010)   /* PCI config base address MBARL register */
#define TEMPE_PCI_MBARU     (0x014)   /* PCI config base address MBARU register */
#define TEMPE_PCI_SUBID     (0x02C)   /* PCI config space Subsystem ID register */
#define TEMPE_PCI_CAPP      (0x034)   /* PCI config capabilities pointer register */
#define TEMPE_PCI_MISC1     (0x03C)   /* PCI config miscellaneous 1 regster */
#define TEMPE_PCI_PCIXCAP   (0x040)   /* PCI config PCI-X capabilities register */
#define TEMPE_PCI_PCIXSTAT  (0x044)   /* PCI config PCI-X status register */

#define TEMPE_LCSR_BASE     (0x100)

/* LCSR - Outbound Translation (x) control register */
#define TEMPE_OTSAU(x)      (0x100 + ((x) * 0x20))
#define TEMPE_OTSAL(x)      (0x104 + ((x) * 0x20))
#define TEMPE_OTEAU(x)      (0x108 + ((x) * 0x20))
#define TEMPE_OTEAL(x)      (0x10C + ((x) * 0x20))
#define TEMPE_OTOFU(x)      (0x110 + ((x) * 0x20))
#define TEMPE_OTOFL(x)      (0x114 + ((x) * 0x20))
#define TEMPE_OTBS(x)       (0x118 + ((x) * 0x20))
#define TEMPE_OTAT(x)       (0x11C + ((x) * 0x20))

/* VMEbus IACK (1-7) Register - 0 is not VALID */
#define TEMPE_VIACK(x)      (0x200 + ((x) * 0x4))

/* RMW */
#define TEMPE_RMWAU         0x220
#define TEMPE_RMWAL         0x224
#define TEMPE_RMWEN         0x228
#define TEMPE_RMWC          0x22C
#define TEMPE_RMWS          0x230

/* VMEbus Control */
#define TEMPE_VMCTRL        0x234
#define TEMPE_VCTRL         0x238
#define TEMPE_VSTAT         0x23C

/* PCI/X Status */
#define TEMPE_PCSR          0x240

/* VME Filter */
#define TEMPE_VMEFL         0x250

/* VME Exception Status */
#define TEMPE_VEAU          0x260
#define TEMPE_VEAL          0x264
#define TEMPE_VEAT          0x268

/* PCI/X Error Status */
#define TEMPE_EDPAU         0x270
#define TEMPE_EDPAL         0x274
#define TEMPE_EDPXA         0x278
#define TEMPE_EDPXS         0x27C
#define TEMPE_EDPAT         0x280

/* Inbound Translation (x) control register */
#define TEMPE_ITSAU(x)      (0x300 + ((x) * 0x20))
#define TEMPE_ITSAL(x)      (0x304 + ((x) * 0x20))
#define TEMPE_ITEAU(x)      (0x308 + ((x) * 0x20))
#define TEMPE_ITEAL(x)      (0x30C + ((x) * 0x20))
#define TEMPE_ITOFU(x)      (0x310 + ((x) * 0x20))
#define TEMPE_ITOFL(x)      (0x314 + ((x) * 0x20))
#define TEMPE_ITAT(x)       (0x318 + ((x) * 0x20))

/* Inbound Translation GCSR */
#define TEMPE_GBAU          0x400
#define TEMPE_GBAL          0x404
#define TEMPE_GCSRAT        0x408

/* Inbound Translation CRG */
#define TEMPE_CBAU          0x40C
#define TEMPE_CBAL          0x410
#define TEMPE_CRGAT         0x414

/* Inbound Translation CR/CSR */
#define TEMPE_CROU          0x418
#define TEMPE_CROL          0x41C
#define TEMPE_CRAT          0x420

/* Inbound Translation Location Monitor */
#define TEMPE_LMBAU         0x424
#define TEMPE_LMBAL         0x428
#define TEMPE_LMAT          0x42C

/* VMEbus Interrupt Control */
#define TEMPE_64BCU         0x430
#define TEMPE_64BCL         0x434
#define TEMPE_BPGTR         0x438
#define TEMPE_BPCTR         0x43C
#define TEMPE_VICR          0x440

/* Local Bus Interrupt Control */
#define TEMPE_INTEN         0x448
#define TEMPE_INTEO         0x44C
#define TEMPE_INTS          0x450
#define TEMPE_INTC          0x454
#define TEMPE_INTM1         0x458
#define TEMPE_INTM2         0x45C

/* DMA Controllers 0 and 1 */
#define TEMPE_DCTL(x)       (0x500 + ((x) * 0x80))
#define TEMPE_DSTA(x)       (0x504 + ((x) * 0x80))
#define TEMPE_DCSAU(x)      (0x508 + ((x) * 0x80))
#define TEMPE_DCSAL(x)      (0x50C + ((x) * 0x80))
#define TEMPE_DCDAU(x)      (0x510 + ((x) * 0x80))
#define TEMPE_DCDAL(x)      (0x514 + ((x) * 0x80))
#define TEMPE_DCLAU(x)      (0x518 + ((x) * 0x80))
#define TEMPE_DCLAL(x)      (0x51C + ((x) * 0x80))
#define TEMPE_DSAU(x)       (0x520 + ((x) * 0x80))
#define TEMPE_DSAL(x)       (0x524 + ((x) * 0x80))
#define TEMPE_DDAU(x)       (0x528 + ((x) * 0x80))
#define TEMPE_DDAL(x)       (0x52C + ((x) * 0x80))
#define TEMPE_DSAT(x)       (0x530 + ((x) * 0x80))
#define TEMPE_DDAT(x)       (0x534 + ((x) * 0x80))
#define TEMPE_DNLAU(x)      (0x538 + ((x) * 0x80))
#define TEMPE_DNLAL(x)      (0x53C + ((x) * 0x80))
#define TEMPE_DCNT(x)       (0x540 + ((x) * 0x80))
#define TEMPE_DDBS(x)       (0x544 + ((x) * 0x80))

/* GCSR Register Group */

/* Header */
#define TEMPE_DEVI_VENI         0x600

/* Control */
#define TEMPE_GCTRL             0x604

/* Semaphore - Byte size registers */
#define TEMPE_SEMAR0            0x608
#define TEMPE_SEMAR1            0x60C
#define TEMPE_SRMAR0_SEMA0      0x608
#define TEMPE_SRMAR0_SEMA1      0x609
#define TEMPE_SRMAR0_SEMA2      0x60A
#define TEMPE_SRMAR0_SEMA3      0x60B
#define TEMPE_SRMAR1_SEMA4      0x60C
#define TEMPE_SRMAR1_SEMA5      0x60D
#define TEMPE_SRMAR1_SEMA6      0x60E
#define TEMPE_SRMAR1_SEMA7      0x60F

/* Mail Box */
#define TEMPE_MBOX(x)           (0x610 + ((x) * 0x4))

/* CR/CSR Register Group */

/* CSR */
#define TEMPE_CSRBCR            0xFF4
#define TEMPE_CSRBSR            0xFF8
#define TEMPE_CBAR              0xFFC


/* Bit fields in the Tempe */

/* PCI Configuration space control and status register */
#define TEMPE_PCI_CSR__D_PE                  0x80000000
#define TEMPE_PCI_CSR__S_SERR                0x40000000
#define TEMPE_PCI_CSR__R_MA                  0x20000000
#define TEMPE_PCI_CSR__R_TA                  0x10000000
#define TEMPE_PCI_CSR__S_TA                  0x08000000
#define TEMPE_PCI_CSR__DEVSEL                0x06000000
#define TEMPE_PCI_CSR__DP_D                  0x01000000
#define TEMPE_PCI_CSR__TFBBC                 0x00800000
#define TEMPE_PCI_CSR__MFBBC                 0x00000200
#define TEMPE_PCI_CSR__SERR_EN               0x00000100
#define TEMPE_PCI_CSR__WAIT                  0x00000080
#define TEMPE_PCI_CSR__PERESP                0x00000040
#define TEMPE_PCI_CSR__VGAPS                 0x00000020
#define TEMPE_PCI_CSR__MWI_EN                0x00000010
#define TEMPE_PCI_CSR__SC                    0x00000008
#define TEMPE_PCI_CSR__BM                    0x00000004
#define TEMPE_PCI_CSR__MS                    0x00000002
#define TEMPE_PCI_CSR__IOS                   0x00000001


/* LCSR Register Group Description */

/* Outbound Translation bit definitions and masks */

#define TEMPE_OTATLx_STAL_MASK      (0xffff0000)
#define TEMPE_OTEALx_ENDL_MASK      (0xffff0000)
#define TEMPE_OTOFLx_OFFL_MASK      (0xffff0000)
#define TEMPE_OTOFLx_2eBS_MASK      (0x001fffff) /* Broadcast Select Mask */

/* Outbound Translation Attribute Register */
#define TEMPE_OTATx_EN              (0x80000000)
#define TEMPE_OTATx_MRPFD           (0x00040000)
#define TEMPE_OTATx_PFS(x)          (0x00010000 << x)
#define TEMPE_OTATx_PFSx_MASK		(0x00030000)
#define TEMPE_OTATx_2eSSTMx_MASK	(0x00003800)
#define TEMPE_OTATx_TM(x)           (0x00000100 << x)
#define TEMPE_OTATx_TMx_MASK		(0x00000700)
#define TEMPE_OTATx_DBW_D16         (0x00000000)
#define TEMPE_OTATx_DBW_D32         (0x00000040)
#define TEMPE_OTATx_DBWx_MASK		(0x000000C0)
#define TEMPE_OTATx_SUP             (0x00000020)
#define TEMPE_OTATx_PGM             (0x00000010)
#define TEMPE_OTATx_AMODE(x)        (0x00000001 << x)
#define TEMPE_OTATx_AMODEx_MASK		(0x0000000F)

/* Outbound Translation Attribute Register PFS (Prefetch Size) */
#define TEMPE_OTATx_PFS_2_CACHE_LINE  (0x00000000)
#define TEMPE_OTATx_PFS_4_CACHE_LINE  (0x00010000)
#define TEMPE_OTATx_PFS_8_CACHE_LINE  (0x00020000)
#define TEMPE_OTATx_PFS_16_CACHE_LINE (0x00030000)

#define TEMPE_OTBS_MASK               (0x001FFFFF)

/* Outbound Translation Attribute Register 2eSST Transfer Rate 
   These are generic for all Attribute Registers that have TM */
#define TEMPE_SSTM_160MByte_sec (0x00000000)
#define TEMPE_SSTM_267MByte_sec (0x00000800)
#define TEMPE_SSTM_320MByte_sec (0x00001000)

/* Outbound Translation Attribute Register VMEbus Transfer Mode 
   These are generic for all Attribute Registers that have TM */
#define TEMPE_TM_SCT                (0x00000000)
#define TEMPE_TM_BLT                (0x00000100)
#define TEMPE_TM_MBLT               (0x00000200)
#define TEMPE_TM_2eVME              (0x00000300)
#define TEMPE_TM_2eSST              (0x00000400)
#define TEMPE_TM_2eSST_BROADCAST    (0x00000500)

#define TEMPE_TM_MASK               (0x00000700)

/* Outbound Translation Attribute Register VMEbus Data Bus Width 
   These are generic for all Attribute Registers that have DBW */
#define TEMPE_DBW_16_bit  (0x00000000)
#define TEMPE_DBW_32_bit  (0x00000040)

/* Attribute Register VMEbus Address Mode 
   These are generic for all Attribute Registers that have AMODE */
#define TEMPE_AMODE_A16     (0x00000000)
#define TEMPE_AMODE_A24	    (0x00000001)
#define TEMPE_AMODE_A32	    (0x00000002)
#define TEMPE_AMODE_A64	    (0x00000004)
#define TEMPE_AMODE_CSR	    (0x00000005)
#define TEMPE_AMODE_USER1	(0x00000008)
#define TEMPE_AMODE_USER2	(0x00000009)
#define TEMPE_AMODE_USER3	(0x0000000A)
#define TEMPE_AMODE_USER4	(0x0000000B)


/* VME Master Control Register bit definitions and masks */
#define TEMPE_VMCTRL_VSA        (0x08000000)
#define TEMPE_VMCTRL_VS         (0x04000000)
#define TEMPE_VMCTRL_DHB        (0x02000000)
#define TEMPE_VMCTRL_DWB        (0x01000000)
#define TEMPE_VMCTRL_RMWEN      (0x00100000)
#define TEMPE_VMCTRL_A64DS      (0x00010000)
#define TEMPE_VMCTRL_VTOFF_MASK (0x00007000)
#define TEMPE_VMCTRL_VTON_MASK  (0x00000700)
#define TEMPE_VMCTRL_VREL_MASK  (0x00000018)
#define TEMPE_VMCTRL_VFAIR      (0x00000004)
#define TEMPE_VMCTRL_VREQL_MASK (0x00000003)

/* VTOFF - VME Master Time Off */
#define TEMPE_VMCTRL_VTOFF_0us  (0x00000000)   
#define TEMPE_VMCTRL_VTOFF_1us  (0x00001000)   
#define TEMPE_VMCTRL_VTOFF_2us  (0x00002000)   
#define TEMPE_VMCTRL_VTOFF_4us  (0x00003000)   
#define TEMPE_VMCTRL_VTOFF_8us  (0x00004000)   
#define TEMPE_VMCTRL_VTOFF_16us (0x00005000)   
#define TEMPE_VMCTRL_VTOFF_32us (0x00006000)   
#define TEMPE_VMCTRL_VTOFF_64us (0x00007000)   

/* VTON - VME Master Time On */
#define TEMPE_VMCTRL_VTON_4us_128byte       (0x00000000)
#define TEMPE_VMCTRL_VTON_8us_128byte       (0x00000100)
#define TEMPE_VMCTRL_VTON_16us_128byte      (0x00000200)
#define TEMPE_VMCTRL_VTON_32us_256byte      (0x00000300)
#define TEMPE_VMCTRL_VTON_64us_512byte      (0x00000400)
#define TEMPE_VMCTRL_VTON_128us_1024byte    (0x00000500)
#define TEMPE_VMCTRL_VTON_256us_2048byte    (0x00000600)
#define TEMPE_VMCTRL_VTON_512us_4196byte    (0x00000700)

/* VREL - VME Master Release Mode */
#define TEMPE_VMCTRL_VREL_TIME_ON_OR_DONE          (0x00000000)
#define TEMPE_VMCTRL_VREL_TIME_ON_AND_REQ_OR_DONE  (0x00000008)
#define TEMPE_VMCTRL_VREL_TIME_ON_AND_BCLR_OR_DONE (0x00000010)
#define TEMPE_VMCTRL_VREL_TIME_ON_OR_DONE_AND_REQ  (0x00000018)

/* VREQL - VME Master Request Level */
#define TEMPE_VMCTRL_VREQL_0		(0x00000000)
#define TEMPE_VMCTRL_VREQL_1		(0x00000001)
#define TEMPE_VMCTRL_VREQL_2		(0x00000002)
#define TEMPE_VMCTRL_VREQL_3		(0x00000003)

/* VMEbus Control Register */
#define TEMPE_VCTRL_DLT_MASK        (0x0F000000)
#define TEMPE_VCTRL_NELBB           (0x00100000)
#define TEMPE_VCTRL_SRESET          (0x00020000)
#define TEMPE_VCTRL_LRESET          (0x00010000)
#define TEMPE_VCTRL_SFAILAI         (0x00008000)
#define TEMPE_VCTRL_BID             (0x00001F00)
#define TEMPE_VCTRL_ATOEN           (0x00000080)
#define TEMPE_VCTRL_ROBIN           (0x00000040)
#define TEMPE_VCTRL_GTO_MASK        (0x0000000F)

#define TEMPE_VCTRL_BID_BIT         (8)


/* VCTRL - Deadlock Timer */
#define TEMPE_VCTRL_DLT_DISABLED    (0x00000000)
#define TEMPE_VCTRL_DLT_16_VCLKs    (0x01000000)
#define TEMPE_VCTRL_DLT_32_VCLKs    (0x02000000)
#define TEMPE_VCTRL_DLT_64_VCLKs    (0x03000000)
#define TEMPE_VCTRL_DLT_128_VCLKs   (0x04000000)
#define TEMPE_VCTRL_DLT_256_VCLKs   (0x05000000)
#define TEMPE_VCTRL_DLT_512_VCLKs   (0x06000000)
#define TEMPE_VCTRL_DLT_1024_VCLKs  (0x07000000)
#define TEMPE_VCTRL_DLT_2048_VCLKs  (0x08000000)
#define TEMPE_VCTRL_DLT_4096_VCLKs  (0x09000000)
#define TEMPE_VCTRL_DLT_8192_VCLKs  (0x0A000000)
#define TEMPE_VCTRL_DLT_16384_VCLKs (0x0B000000)
#define TEMPE_VCTRL_DLT_32768_VCLKs (0x0C000000)

/* VCTRL - VMEbus Global Time-out */
#define TEMPE_VCTRL_GTO_8us         (0x00000000)
#define TEMPE_VCTRL_GTO_16us        (0x00000001)
#define TEMPE_VCTRL_GTO_32us        (0x00000002)
#define TEMPE_VCTRL_GTO_64us        (0x00000003)
#define TEMPE_VCTRL_GTO_128us       (0x00000004)
#define TEMPE_VCTRL_GTO_256us       (0x00000005)
#define TEMPE_VCTRL_GTO_512us       (0x00000006)
#define TEMPE_VCTRL_GTO_1024us      (0x00000007)
#define TEMPE_VCTRL_GTO_2048us      (0x00000008)
#define TEMPE_VCTRL_GTO_DISABLED    (0x0000000F)


/* VMEbus Status Register */
#define TEMPE_VSTAT_CPURST          (0x00008000)
#define TEMPE_VSTAT_BDFAIL          (0x00004000)
#define TEMPE_VSTAT_PURSTS          (0x00001000)
#define TEMPE_VSTAT_BDFAILS         (0x00000800)
#define TEMPE_VSTAT_SYSFLS          (0x00000400)
#define TEMPE_VSTAT_ACFAILS         (0x00000200)
#define TEMPE_VSTAT_SCONS           (0x00000100)
#define TEMPE_VSTAT_GAP             (0x00000020)
#define TEMPE_VSTAT_GA_MASK         (0x0000001F)


/* PCI/X Control / Status Register */
#define TEMPE_PCSR_SRTO_MASK        (0x07000000)
#define TEMPE_PCSR_SRTT             (0x00400000)
#define TEMPE_PCSR_CCTM             (0x00200000)
#define TEMPE_PCSR_DRQ              (0x00100000)
#define TEMPE_PCSR_DTTT             (0x00080000)
#define TEMPE_PCSR_MRCT             (0x00040000)
#define TEMPE_PCSR_MRC              (0x00020000)
#define TEMPE_PCSR_SBH              (0x00010000)
#define TEMPE_PCSR_SRTE             (0x00000400)
#define TEMPE_PCSR_DTTE             (0x00000200)
#define TEMPE_PCSR_MRCE             (0x00000100)
#define TEMPE_PCSR_REQ64S           (0x00000040)
#define TEMPE_PCSR_M66ENS           (0x00000020)
#define TEMPE_PCSR_FRAMES           (0x00000010)
#define TEMPE_PCSR_IRDYS            (0x00000008)
#define TEMPE_PCSR_DEVSELS          (0x00000004)
#define TEMPE_PCSR_STOPS            (0x00000002)
#define TEMPE_PCSR_TRDYS            (0x00000001)

/* VMEbus Filter Register */
#define TEMPE_VMEFL_ACKD_MASK       (0x03000000)
#define TEMPE_VMEFL_BGFC            (0x00000800)
#define TEMPE_VMEFL_BRFC            (0x00000400)
#define TEMPE_VMEFL_BCFC            (0x00000200)
#define TEMPE_VMEFL_BBFC            (0x00000100)
#define TEMPE_VMEFL_AKFC            (0x00000010)
#define TEMPE_VMEFL_STFC            (0x00000001)

/* VMEbus Filter Register - Acknowledge Delay Time */
#define TEMPE_VMEFL_ACKD_SLOW       (0x00000000)
#define TEMPE_VMEFL_ACKD_MEDIUM     (0x01000000)
#define TEMPE_VMEFL_ACKD_FAST       (0x02000000)

/* VMEbus Exception Attributes Register */
#define TEMPE_VEAT_VES              (0x80000000)
#define TEMPE_VEAT_VEOF             (0x40000000)
#define TEMPE_VEAT_VESCL            (0x20000000)
#define TEMPE_VEAT_2eOT             (0x00200000)
#define TEMPE_VEAT_2eST             (0x00100000)
#define TEMPE_VEAT_BERR             (0x00080000)
#define TEMPE_VEAT_LWORD            (0x00040000)
#define TEMPE_VEAT_WRITE            (0x00020000)
#define TEMPE_VEAT_IACK             (0x00010000)
#define TEMPE_VEAT_DS1              (0x00008000)
#define TEMPE_VEAT_DS0              (0x00004000)
#define TEMPE_VEAT_AM_MASK          (0x00003F00)
#define TEMPE_VEAT_XAM_MASK         (0x000000FF)


/* Error Diagnostic PCI/X Attributes Register */
#define TEMPE_EDPAT_EDPST           (0x80000000)
#define TEMPE_EDPAT_EDPOF           (0x40000000)
#define TEMPE_EDPAT_EDPCL           (0x20000000)
#define TEMPE_EDPAT_SCD             (0x00020000)
#define TEMPE_EDPAT_USC             (0x00010000)
#define TEMPE_EDPAT_SRT             (0x00008000)
#define TEMPE_EDPAT_SCEM            (0x00004000)
#define TEMPE_EDPAT_DPED            (0x00002000)
#define TEMPE_EDPAT_DPE             (0x00001000)
#define TEMPE_EDPAT_MRC             (0x00000800)
#define TEMPE_EDPAT_RMA             (0x00000400)
#define TEMPE_EDPAT_RTA             (0x00000200)
#define TEMPE_EDPAT_DTT             (0x00000100)
#define TEMPE_EDPAT_CBEA3           (0x00000080)
#define TEMPE_EDPAT_CBEA2           (0x00000040)
#define TEMPE_EDPAT_CBEA1           (0x00000020)
#define TEMPE_EDPAT_CBEA0           (0x00000010)
#define TEMPE_EDPAT_COMM3           (0x00000008)
#define TEMPE_EDPAT_COMM2           (0x00000004)
#define TEMPE_EDPAT_COMM1           (0x00000002)
#define TEMPE_EDPAT_COMM0           (0x00000001)

#define TEMPE_ITSALx_STAL_MASK		(0xFFFFFFF0)
#define TEMPE_ITEALx_ENDAL_MASK		(0xFFFFFFF0)
#define TEMPE_ITOFLx_OFFL_MASK		(0xFFFFFFF0)

/* Inbound Translation Attribute (0-7) Registers */
#define TEMPE_ITATx_EN              (0x80000000)
#define TEMPE_ITATx_TH              (0x00040000)
#define TEMPE_ITATx_VFS_MASK        (0x00030000)
#define TEMPE_ITATx_2eSSTM_MASK     (0x00007000)
#define TEMPE_ITATx_2eSSTB          (0x00000800)
#define TEMPE_ITATx_2eSST           (0x00000400)
#define TEMPE_ITATx_2eVME           (0x00000200)
#define TEMPE_ITATx_MBLT            (0x00000100)
#define TEMPE_ITATx_BLT             (0x00000080)
#define TEMPE_ITATx_AS_MASK         (0x00000070)
#define TEMPE_ITATx_SUPR            (0x00000008)
#define TEMPE_ITATx_NPRIV           (0x00000004)
#define TEMPE_ITATx_PGM             (0x00000002)
#define TEMPE_ITATx_DATA            (0x00000001)

#define TEMPE_ITATx_CTL__PGM__BOTH (TEMPE_ITATx_PGM | TEMPE_ITATx_DATA)
#define TEMPE_ITATx_CTL__SUPER__BOTH (TEMPE_ITATx_SUPR | TEMPE_ITATx_NPRIV)

/* Inbound Translation Attribute - Virtual FIFO Size */
#define TEMPE_ITATx_VFS_64_BYTE     (0x00000000)
#define TEMPE_ITATx_VFS_128_BYTE    (0x00010000)
#define TEMPE_ITATx_VFS_256_BYTE    (0x00020000)
#define TEMPE_ITATx_VFS_512_BYTE    (0x00030000)

/* Inbound Translation Attribute - 2eSST Mode */
#define TEMPE_ITATx_2eSSTM_160MByte_sec (0x00000000)
#define TEMPE_ITATx_2eSSTM_267MByte_sec (0x00001000)
#define TEMPE_ITATx_2eSSTM_320MByte_sec (0x00002000)

/* Inbound Translation Attribute - VMEbus Address Space */
#define TEMPE_ITATx_AS_A16  (0x00000000)
#define TEMPE_ITATx_AS_A24	(0x00000010)
#define TEMPE_ITATx_AS_A32	(0x00000020)
#define TEMPE_ITATx_AS_A64	(0x00000040)

/* GCSR Base Address Lower */ 
#define TEMPE_GBAL_OFFL_MASK    (0xFFFFFFE0)

/* GCSR Attribute Register */
#define TEMPE_GCSRAT_EN         (0x00000080)
#define TEMPE_GCSRAT_AS_MASK    (0x00000070)
#define TEMPE_GCSRAT_SUPR       (0x00000008)
#define TEMPE_GCSRAT_NPRIV      (0x00000004)
#define TEMPE_GCSRAT_PGM        (0x00000002)
#define TEMPE_GCSRAT_DATA       (0x00000001)

#define TEMPE_GCSRAT_AS_A16     (0x00000000)
#define TEMPE_GCSRAT_AS_A24	    (0x00000010)
#define TEMPE_GCSRAT_AS_A32	    (0x00000020)
#define TEMPE_GCSRAT_AS_A64	    (0x00000040)

/* CRG Base Address Lower */ 
#define TEMPE_CBAL_MASK         (0xFFFFF000)

/* CRG Attribute Register */
#define TEMPE_CRGAT_EN          (0x00000080)
#define TEMPE_CRGAT_AS_MASK     (0x00000070)
#define TEMPE_CRGAT_SUPR        (0x00000008)
#define TEMPE_CRGAT_NPRIV       (0x00000004)
#define TEMPE_CRGAT_PGM         (0x00000002)
#define TEMPE_CRGAT_DATA        (0x00000001)

#define TEMPE_CRG_CTL__PGM__BOTH (TEMPE_CRGAT_PGM | TEMPE_CRGAT_DATA)
#define TEMPE_CRG_CTL__SUPER__BOTH (TEMPE_CRGAT_SUPR | TEMPE_CRGAT_NPRIV)

#define TEMPE_CRGAT_AS_A16      (0x00000000)
#define TEMPE_CRGAT_AS_A24	    (0x00000010)
#define TEMPE_CRGAT_AS_A32	    (0x00000020)
#define TEMPE_CRGAT_AS_A64	    (0x00000040)

#define TEMPE_CROL_MASK         (0xFF800000)

/* CR/CSR Attribute Register */
#define TEMPE_CRAT_EN           (0x00000080)

/* Location Monitor Base Address Lower Register */
#define TEMPE_LMBAL_MASK        (0xFFFFFFE0)

/* Location Monitor Attribute Register */
#define TEMPE_LMAT_EN           (0x00000080)
#define TEMPE_LMAT_AS_MASK      (0x00000070)
#define TEMPE_LMAT_SUPR         (0x00000008)
#define TEMPE_LMAT_NPRIV        (0x00000004)
#define TEMPE_LMAT_PGM          (0x00000002)
#define TEMPE_LMAT_DATA         (0x00000001)

#define TEMPE_LM_CTL__PGM__BOTH (TEMPE_LMAT_PGM | TEMPE_LMAT_DATA)
#define TEMPE_LM_CTL__SUPER__BOTH (TEMPE_LMAT_SUPR | TEMPE_LMAT_NPRIV)

#define TEMPE_LMAT_AS_A16       (0x00000000)
#define TEMPE_LMAT_AS_A24	    (0x00000010)
#define TEMPE_LMAT_AS_A32	    (0x00000020)
#define TEMPE_LMAT_AS_A64	    (0x00000040)


/* VMEbus Interrupt Control Register */
#define TEMPE_VICR_CNTS_MASK    (0xC0000000)
#define TEMPE_VICR_EDGIS_MASK   (0x30000000)
#define TEMPE_VICR_IRQ1F_MASK   (0x0C000000)
#define TEMPE_VICR_IRQ2F_MASK   (0x03000000)
#define TEMPE_VICR_BIP          (0x00800000)
#define TEMPE_VICR_BIPS         (0x00400000)
#define TEMPE_VICR_IRQC         (0x00008000)
#define TEMPE_VICR_IRQLS_MASK   (0x00007000)
#define TEMPE_VICR_IRQS         (0x00000800)
#define TEMPE_VICR_IRQL_MASK    (0x00000700)
#define TEMPE_VICR_IRQL_BIT	    (8)
#define TEMPE_VICR_STID_MASK    (0x000000FF)

#define TEMPE_VICR_CNTS_COUNTER_DISABLE  (0x00000000)
#define TEMPE_VICR_CNTS_IRQ1I_to_COUNTER (0x40000000)
#define TEMPE_VICR_CNTS_IRQ2I_to_COUNTER (0x80000000)

#define TEMPE_VICR_EDGIS_DISABLE            (0x00000000)
#define TEMPE_VICR_EDGIS_IRQ1I_to_EDGE_INT  (0x10000000)
#define TEMPE_VICR_EDGIS_IRQ2I_to_EDGE_INT  (0x20000000)

#define TEMPE_VICR_IRQ1F_NORMAL         (0x00000000)
#define TEMPE_VICR_IRQ1F_PULSE_GEN      (0x04000000)
#define TEMPE_VICR_IRQ1F_PRGM_CLOCK     (0x08000000)
#define TEMPE_VICR_IRQ1F_1_02us_CLOCK   (0x0C000000)

#define TEMPE_VICR_IRQ2F_NORMAL         (0x00000000)
#define TEMPE_VICR_IRQ2F_PULSE_GEN      (0x01000000)
#define TEMPE_VICR_IRQ2F_PRGM_CLOCK     (0x02000000)
#define TEMPE_VICR_IRQ2F_1_02us_CLOCK   (0x03000000)

/* Interrupt Enable Register */
/* To get the bit to enable, use INT_ENUM_TO_BIT() with
   a value from the table below */

/* Tempe interrupt enumeration, you can use the enum as a bit shift
   in the IER, IEOR and ISR */
typedef enum
{
  INT_RESERVED_0 = 0,
  INT_IRQ1,
  INT_IRQ2,
  INT_IRQ3,
  INT_IRQ4,
  INT_IRQ5,
  INT_IRQ6,
  INT_IRQ7,
  INT_ACFL,
  INT_SYSFL,
  INT_IACK,
  INT_VME_IRQ_EDGE,
  INT_VME_ERR,
  INT_PCI_ERR,
  INT_RESERVED_14,
  INT_RESERVED_15,
  INT_MBOX_0,
  INT_MBOX_1,
  INT_MBOX_2,
  INT_MBOX_3,
  INT_LM_0,
  INT_LM_1,
  INT_LM_2,
  INT_LM_3,
  INT_DMA_0,
  INT_DMA_1,
  INT_RESERVED_26,
  INT_RESERVED_27,
  INT_RESERVED_28,
  INT_RESERVED_29,
  INT_RESERVED_30,
  INT_RESERVED_31
} TEMPE_INT_LEVEL;

#define INT_BIT_TO_ENUM(x) ( log(x)/log(2) )
#define INT_ENUM_TO_BIT(x) (1 << x)

#define INT_VIRQ_ALL  0x000000FE
#define INT_MBOX_MASK 0x000F0000
#define INT_LM_MASK   0x00F00000
#define INT_DMA_MASK  0x03000000

#define BIT_INT_DMA_1           0x02000000
#define BIT_INT_DMA_0           0x01000000
#define BIT_INT_LM_3            0x00800000
#define BIT_INT_LM_2            0x00400000
#define BIT_INT_LM_1            0x00200000
#define BIT_INT_LM_0            0x00100000
#define BIT_INT_MBOX_3          0x00080000
#define BIT_INT_MBOX_2          0x00040000
#define BIT_INT_MBOX_1          0x00020000
#define BIT_INT_MBOX_0          0x00010000
#define BIT_INT_PCI_ERR         0x00002000
#define BIT_INT_VME_ERR         0x00001000
#define BIT_INT_VME_IRQ_EDGE    0x00000800
#define BIT_INT_IACK            0x00000400
#define BIT_INT_SYSFAIL         0x00000200
#define BIT_INT_ACFAIL          0x00000100
#define BIT_INT_IRQ7            0x00000080
#define BIT_INT_IRQ6            0x00000040
#define BIT_INT_IRQ5            0x00000020
#define BIT_INT_IRQ4            0x00000010
#define BIT_INT_IRQ3            0x00000008
#define BIT_INT_IRQ2            0x00000004
#define BIT_INT_IRQ1            0x00000002
#define BIT_INT_IRQ_ALL         0x000000FE

/* Interrupt Enable Out Register
   To get the bit to enable, use INT_ENUM_TO_BIT() with
   a value from the table */

/* Interrupt Status Register 
   To get the bit to check, use INT_ENUM_TO_BIT() with
   a value from the table */

/* Interrupt Clear Register
   To get the bit to clear, use INT_ENUM_TO_BIT() with
   a value from the table */

/* Interrupt Map 1 Register */
/* Do we want to support routing PCI interrupts to 
   anything other then PCI INTA ? the SBC would need
   to connect INTA - INTD for this to work. */

/* DMA Control Registers */
#define TEMPE_DCTLx_ABT       (0x08000000)
#define TEMPE_DCTLx_PAU       (0x04000000)
#define TEMPE_DCTLx_DGO       (0x02000000)
#define TEMPE_DCTLx_MOD       (0x00800000)
#define TEMPE_DCTLx_VFAR      (0x00020000)
#define TEMPE_DCTLx_PFAR      (0x00010000)

#define TEMPE_DCTLx_VBKS_MASK (0x00007000)
#define TEMPE_DCTLx_VBOT_MASK (0x00000700)
#define TEMPE_DCTLx_PBKS_MASK (0x00000070)
#define TEMPE_DCTLx_PBOT_MASK (0x00000007)

#define TEMPE_DCTLx_VBKS_32_BYTES   (0x00000000)
#define TEMPE_DCTLx_VBKS_64_BYTES   (0x00001000)
#define TEMPE_DCTLx_VBKS_128_BYTES  (0x00002000)
#define TEMPE_DCTLx_VBKS_256_BYTES  (0x00003000)
#define TEMPE_DCTLx_VBKS_512_BYTES  (0x00004000)
#define TEMPE_DCTLx_VBKS_1024_BYTES (0x00005000)
#define TEMPE_DCTLx_VBKS_2048_BYTES (0x00006000)
#define TEMPE_DCTLx_VBKS_4096_BYTES (0x00007000)

#define TEMPE_DCTLx_VBOT_0_us  (0x00000000)
#define TEMPE_DCTLx_VBOT_1_us  (0x00000100)
#define TEMPE_DCTLx_VBOT_2_us  (0x00000200)
#define TEMPE_DCTLx_VBOT_4_us  (0x00000300)
#define TEMPE_DCTLx_VBOT_8_us  (0x00000400)
#define TEMPE_DCTLx_VBOT_16_us (0x00000500)
#define TEMPE_DCTLx_VBOT_32_us (0x00000600)
#define TEMPE_DCTLx_VBOT_64_us (0x00000700)

#define TEMPE_DCTLx_PBKS_32_BYTES   (0x00000000)
#define TEMPE_DCTLx_PBKS_64_BYTES   (0x00000010)
#define TEMPE_DCTLx_PBKS_128_BYTES  (0x00000020)
#define TEMPE_DCTLx_PBKS_256_BYTES  (0x00000030)
#define TEMPE_DCTLx_PBKS_512_BYTES  (0x00000040)
#define TEMPE_DCTLx_PBKS_1024_BYTES (0x00000050)
#define TEMPE_DCTLx_PBKS_2048_BYTES (0x00000060)
#define TEMPE_DCTLx_PBKS_4096_BYTES (0x00000070)

#define TEMPE_DCTLx_PBOT_0_us   (0x00000000)
#define TEMPE_DCTLx_PBOT_1_us   (0x00000001)
#define TEMPE_DCTLx_PBOT_2_us   (0x00000002)
#define TEMPE_DCTLx_PBOT_4_us   (0x00000003)
#define TEMPE_DCTLx_PBOT_8_us   (0x00000004)
#define TEMPE_DCTLx_PBOT_16_us  (0x00000005)
#define TEMPE_DCTLx_PBOT_32_us  (0x00000006)
#define TEMPE_DCTLx_PBOT_64_us  (0x00000007)

/* DMA Status Registers */
#define TEMPE_DSTAx_ERR         (0x10000000)
#define TEMPE_DSTAx_ABT         (0x08000000)
#define TEMPE_DSTAx_PAU         (0x04000000)
#define TEMPE_DSTAx_DON         (0x02000000)
#define TEMPE_DSTAx_BSY         (0x01000000)
#define TEMPE_DSTAx_ERRS        (0x00100000)
#define TEMPE_DSTAx_ERT_MASK    (0x00030000)

/* DMA Current Link Address Lower Register */
#define TEMPE_DCLALx_MASK       (0xFFFFFFC0)

/* DMA Source Attribute Registers */
#define TEMPE_DSATx_TYP_MASK    (0x30000000)
#define TEMPE_DSATx_PSZ         (0x02000000)
#define TEMPE_DSATx_NIP         (0x01000000)

/* DMA Destination Attribute Registers */
#define TEMPE_DDATx_TYP         (0x10000000)

/* DMA Next Link Address Lower Registers */
#define TEMPE_DNLALx_ADDR_MASK  (0xFFFFFFF8)
#define TEMPE_DNLALx_LLA        (0x00000001)

/* DMA Destination Broadcast Select Registers */
#define TEMPE_DDBSx_DDBS_MASK   (0x001FFFFF)

/* GCSR - Control and Status Register */
#define TEMPE_GCTRL_LRST        (0x80000000)
#define TEMPE_GCTRL_SFAILEN     (0x40000000)
#define TEMPE_GCTRL_BDFAILS     (0x20000000)
#define TEMPE_GCTRL_SCONS       (0x10000000)
#define TEMPE_GCTRL_MEM         (0x08000000)
#define TEMPE_GCTRL_LMI3S       (0x00800000)
#define TEMPE_GCTRL_LMI2S       (0x00400000)
#define TEMPE_GCTRL_LMI1S       (0x00200000)
#define TEMPE_GCTRL_LMI0S       (0x00100000)
#define TEMPE_GCTRL_MBI3S       (0x00080000)
#define TEMPE_GCTRL_MBI2S       (0x00040000)
#define TEMPE_GCTRL_MBI1S       (0x00020000)
#define TEMPE_GCTRL_MBI0S       (0x00010000)
#define TEMPE_GCTRL_GAP         (0x00002000)
#define TEMPE_GCTRL_GA_BIT      (8)
#define TEMPE_GCTRL_GA_MASK     (0x00001F00)
#define TEMPE_GCTRL_REVID_MASK  (0x000000FF)


/* CR/CSR Bit Clear Register */
#define TEMPE_CSRBCR_LRSTC      (0x00000080)
#define TEMPE_CSRBCR_SFAILC     (0x00000040)
#define TEMPE_CSRBCR_BDFAILS    (0x00000020)
#define TEMPE_CSRBCR_MENC       (0x00000010)
#define TEMPE_CSRBCR_BERRSC     (0x00000008)

/* CR/CSR Bit Status Register */
#define TEMPE_CSRBSR_LRSTS      (0x00000080)
#define TEMPE_CSRBSR_SFAILS     (0x00000040)
#define TEMPE_CSRBSR_BDFAILS    (0x00000020)
#define TEMPE_CSRBSR_MENS       (0x00000010)
#define TEMPE_CSRBSR_BERRSS     (0x00000008)

/* CR/CSR Base Address Register */
#define TEMPE_CBAR_MASK         (0x000000F8)

/* Layout of a DMAC Linked-List Descriptor */
typedef struct _TEMPE_DMA_DESCRIPTOR 
{
    GEF_UINT32 dsau;    /* Source Address */
    GEF_UINT32 dsal;
    GEF_UINT32 ddau;    /* Destination Address */
    GEF_UINT32 ddal;
    GEF_UINT32 dsat;    /* Source attributes */
    GEF_UINT32 ddat;    /* Destination attributes */
    GEF_UINT32 dnlau;   /* Next link address */
    GEF_UINT32 dnlal;
    GEF_UINT32 dcnt;    /* Byte count */
    GEF_UINT32 ddbs;    /* 2eSST Broadcast select */
} TEMPE_DMA_DESCRIPTOR;

#endif /* __GEFCMN_VME_TEMPE_H */

