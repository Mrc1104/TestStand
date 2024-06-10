#!/bin/bash

handle_error(){
	echo "\n------------------------\n"
	echo "An Error Occurred on line $1"
	exit 1
}

trap 'handle_error $LINENO' ERR

argcnt=$#
run1=4
run2=4
coda=3
rootfile='testing/coda3'
datafile='testing/coda3'
if [ ${argcnt} -eq 1 ] 
	then 
		run1=$1
		run2=$1
fi
if [ ${argcnt} -gt 1 ]
	then
		run1=$1
		run2=$2
	if [ ${argcnt} -gt 2 ]
		then 
			coda=$3
			rootfile='testing/coda2'
			datafile='testing/coda2'
	fi	
fi

echo 
echo "########## 0/3 ##########"
echo
make -C test_build

echo 
echo "########## 1/3 ##########"
echo
test_build/qwmockdatagenerator -r ${run1} -e 1:2000 --config qwparity_simple.conf --detectors mock_detectors.map --data ${datafile}  --coda-version ${coda}

echo 
echo "########## 2/3 ##########"
echo
test_build/qwparity -r ${run1} -e 1:2000 --config qwparity_simple.conf --detectors mock_detectors.map --data ${datafile} --rootfiles ${rootfile} --coda-version ${coda}

echo 
echo "########## 3/3 ##########"
echo
test_build/qwroot -l -q 'testing/compare.C('${coda},${run1},${run2}')'
