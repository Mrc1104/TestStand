#!/bin/bash
set -x
handle_error(){
	echo "\n------------------------\n"
	echo "An error occured on line $1"
	exit 1
}

trap 'handle_error $LINENO' ERR

# Branche list
branches=("bcm_an_us" "bcm_an_ds" "bcm_an_ds3" "bcm_an_ds10" "bcm_dg_us" "bcm_dg_ds" "bcm_dg_usc" "bcm_dg_dsc")
files=("prex" "fork" "japan")

for file in ${files[@]}; do
	echo $file
	for branch in ${branches[@]}; do
		echo $branch
		root -l -q ped_gain.C\(\"${file}\",\"${branch}\"\)
	done
done

