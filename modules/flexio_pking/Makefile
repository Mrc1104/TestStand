#
# File:
#    Makefile
#
# Description:
#    Makefile for the FlexIO library (Paul King's version)
#
#
#
DEBUG=1

ifndef ARCH
ARCH			:= $(shell uname -m)
endif

ifndef LINUXVME_LIB
	LINUXVME_LIB	= ${CODA}/extensions/linuxvme/libs
endif
ifndef LINUXVME_INC
	LINUXVME_INC	= ${CODA}/extensions/linuxvme/include
endif

CROSS_COMPILE		=
CC			= $(CROSS_COMPILE)gcc
AR                      = ar
RANLIB                  = ranlib
CFLAGS			= -O2 -I. -I/usr/include -I$(LINUXVME_INC) -I$(DEVICES_INC)
ifdef DEBUG
CFLAGS			+= -Wall -g
endif

SRC			= flexioLib.c

OBJS			= $(SRC:%.c=%.o)

LIBS			= libflexio.a
SHLIBS			= libflexio.so

ifeq ($(ARCH),x86_64)
	libdir:=/usr/lib64/gef
else
	libdir:=/usr/lib/gef
endif

all: $(LIBS) links

$(SHLIBS): $(SRC) Makefile
	$(CC) -fpic -shared $(CFLAGS) -lrt -lpthread -o $@ $(SRC)

$(LIBS): $(OBJS) Makefile
	$(AR) rv $@ $(OBJS)

clean distclean:
	@rm -f $(OBJS) $(LIBS) $(SHLIBS) *~

links: $(LIBS) $(SHLIBS)
	ln -sf $(PWD)/$(LIBS) $(DEVICES_LIB)/$(LIBS)
	ln -sf $(PWD)/$(SHLIBS) $(DEVICES_LIB)/$(SHLIBS)
	ln -sf $(PWD)/flexioLib.h $(DEVICES_INC)/flexioLib.h

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all clean distclean
