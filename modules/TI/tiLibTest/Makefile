INFILE=
OUTFILE=
INC_GEF=/usr/include/gef/ 
INC_JVME=${CODA}/linuxvme/include/
INC_DIR=${CODA}/linuxvme/ti/test


LIB=/usr/local/coda/3.10_arm/linuxvme/Linux-x86_64/lib
LIB_FLAGS=-lrt -ljvme -lsd -lti -lts

all:
	gcc -o $(OUTFILE) -g $(INFILE) -I $(INC_GEF) -I $(INC_JVME) -L $(LIB) $(LIB_FLAGS)
