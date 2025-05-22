CLOSEDSEGS=(1 5 9 13)
CLOSEDCODE=67

TRANSEGS=(2 4 6 8 10 12 14)
TRANSCODE=84

OPENSEGS=(3 7 11)
OPENCODE=79

SEGS=
CODE=

while [[ "$1" =~ ^- && ! "$1" == "--" ]]; do case $1 in
		-o | --open)
		shift; 
		SEGS=("${OPENSEGS[@]}")
		CODE=("${OPENCODE[@]}")
		echo "CHOSED OPEN"
		;;
		-c | --closed )
		shift; 
		SEGS=("${CLOSEDSEGS[@]}")
		CODE=("${CLOSEDCODE[@]}")
		echo "CHOSED CLOSED"
		;;
		-t | --trans )
		shift;
		SEGS=("${TRANSEGS[@]}")
		CODE=("${TRANSCODE[@]}")
		echo "CHOSED TRANS"
		;;
esac; shift; done
if [[ "$1" == '--' ]]; then shift; fi

for seg in "${SEGS[@]}"; do
	for file in ./*g${seg}_*; do
		echo ${file}
		sed -E -i 's/(\"DetNo\" auxvalue=)\".*\"/\1\"10201'${CODE}'\"/g' ${file}
	done
done
