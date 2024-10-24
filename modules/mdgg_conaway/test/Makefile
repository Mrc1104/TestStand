# test makefile for mdgg-8
INFILE = mdgg_test.c
OUTFILE = mdgg_test
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
LDFLAGS                 = -L$(LINUXVME_LIB) -L. -L..
LIBS                    = -lrt -ljvme -ltir -lMDGG
INCS                    = -I$(LINUXVME_INC) -I. -I.. -I/usr/include  -I${CODA}/common/include
PROGS                   = 
SRC                     = 
OBJ                     = $(SRC:.c=.o)

all: $(OUTFILE)

clean distclean:
	@rm -f $(PROGS) *~ $(OUTFILE)


.PHONY: all clean distclean

$(OUTFILE): $(INFILE)
	$(CC) -fpic $(CFLAGS) $(INCS) $(LDFLAGS) $(LIBS) -o $@ $^
