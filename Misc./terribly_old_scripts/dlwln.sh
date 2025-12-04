#!/bin/bash

# "DownLoad With Link"
# Download online image and write source domain to metadata

enable -n echo

readonly NORMAL="\33[0m"

readonly BOLD="\33[1m"
readonly RED="\33[31m"

SCRIPT_NAME=$(basename $0)

function usage(){
	echo -e "${BOLD}${SCRIPT_NAME} [options] [file]${NORMAL}"
	echo -e "	-h : print this help message"
	echo -e "	-c        : read input from X clipboard"
	echo -e "	-i [URL]  : specify input url"
	echo -e "	-o [file] : specify output file; defaults to inputs base name"
#	echo -e "${YELLOW}${NORMAL}"
}

OPTSTR="hci:o:"

IMG=""
OUTPUT=""

while getopts "${OPTSTR}" O; do
        case $O in
                h) usage && exit ;;
				c) IMG=$(xclip -out -selection clipboard) ;;
                i) IMG=$OPTARG ;;
                o) OUTPUT=$OPTARG ;;
                *) echo -e "${RED}Unrecognized option, exiting...${NORMAL}" && exit 1 ;;
        esac
done
#OPTIND=0

[ -z "$IMG" ] && echo -e "${RED}No input URL specified exiting...${NORMAL}" && exit 1
[ -z "$OUTPUT" ] && OUTPUT=$(basename "$IMG")

curl $IMG --output "$OUTPUT" &> /dev/null
SUC=$?
if ! [ $SUC == "0" ]; then
	echo -e "${RED}Curling the specified URL failed. Exiting...${NORMAL}"
	exit 1
fi

exiftool -overwrite_original -m -ImageDescription="source: $IMG" $OUTPUT &> /dev/null
SUC=$?
if ! [ $SUC == "0" ]; then
	rm "$OUTPUT"
	echo -e "${RED}Error encountered while writing metadata. Exiting...${NORMAL}"
	exit 1
fi
