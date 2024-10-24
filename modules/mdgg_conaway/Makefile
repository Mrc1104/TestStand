# makefile for mdgg-8                                                                                                 

ifndef LINUXVME_LIB
        LINUXVME_LIB    = ${CODA}/extensions/linuxvme/libs
endif

ifndef LINUXVME_INC
        LINUXVME_INC    = ${CODA}/extensions/linuxvme/include
endif

CROSS_COMPILE           =
CC                      = gcc
AR                      = ar
RANLIB                  = ranlib
CFLAGS                  = -Wall -O2 -DLINUX -DJLAB -DDAYTIME=\""`date`"\"
LDFLAGS                 = -L$(LINUXVME_LIB) -L.
LIBS                    = -lrt -ljvme -ltir
INCS                    = -I$(LINUXVME_INC) -I. -I/usr/include  -I${CODA}/common/include
PROGS                   =
SRC                     =
OBJ                     = $(SRC:.c=.o)

all: libMDGG.a

clean distclean:
	@rm -f $(PROGS) *~ *.so *.a


.PHONY: all clean distclean

libMDGG.a: mdgg.c mdgg.h
	$(CC) -fpic -shared $(CFLAGS) $(INCS) -o $(@:.a=.so) $^
	$(AR) ruv  $@ $^
	$(RANLIB)  $@
