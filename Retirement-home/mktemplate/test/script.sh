#!/bin/bash

enable -n echo

readonly NORMAL="\33[0m"

readonly BOLD="\33[1m"
readonly UNDERLINE="\33[4m"
readonly INVERSE="\33[7m"

readonly BLACK="\33[30m"
readonly RED="\33[31m"
readonly GREEN="\33[32m"
readonly YELLOW="\33[33m"
readonly BLUE="\33[34m"
readonly MAGENTA="\33[35m"
readonly CYAN="\33[36m"
readonly WHITE="\33[37m"

SCRIPT_NAME=$(basename $0)

function usage(){
	echo -e "${BOLD}${SCRIPT_NAME} [options] [file]${NORMAL}"
	echo -e "	-h : print this help message"
	echo -e ""
#	echo -e "${YELLOW}${NORMAL}"
}

OPTSTR="h"

while getopts "${OPTSTR}" O; do
        case $O in
				h) usage && exit ;;
                *) echo -e "${RED}Unrecognized option, exiting...${NORMAL}" && exit 1 ;;
        esac
done
#OPTIND=0
