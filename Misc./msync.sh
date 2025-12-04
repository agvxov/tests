#!/bin/bash

enable -n echo

readonly NORMAL="\33[0m"
readonly BOLD="\33[1m"
readonly RED="\33[31m"
readonly YELLOW="\33[33m"
readonly GREEN="\33[32m"


SCRIPT_NAME=$(basename $0)

function usage(){
	echo -e "${BOLD}${SCRIPT_NAME} [options]${NORMAL}"
	echo -e "	-h        : print this help message"
	echo -e "	-i [path] : specifies main Main location"
	echo -e "	-o [path] : specifies Main outpost location"
	echo -e "	-c        : create outpost"
	echo -e "	-m        : merge back outpost"
	echo -e "${YELLOW}This script serves as a utility for creating out posts of Main folders and merging those back.${NORMAL}"
}

OPTSTR="hi:o:cm"

while getopts "${OPTSTR}" O; do
        case $O in
                h) usage && exit ;;
				i) INPUT="${OPTARG}" ;;
				o) OUTPUT="${OPTARG}" ;;
				c) MODE="Create" ;;
				m) MODE="Merge" ;;
                *) echo -e "${RED}Unrecognized option, exiting...${NORMAL}" && exit 1 ;;
        esac
done

[ -z "$INPUT" ] || [ -z "$OUTPUT" ] && echo -e "${RED}No I/O location specified.${NORMAL}" && exit 1

echo -e "${YELLOW}${BOLD}Input Main location:${NORMAL}  ${INPUT}"
echo -e "${YELLOW}${BOLD}Output Main location:${NORMAL} ${OUTPUT}"

source "${INPUT}/Bash/Bashrc/.paths.rc"			# ?!; meditate on this

function _create(){
	echo -e "${YELLOW}Creating outpost...${NORMAL}"

	# Check cleanness
		! [ -s "${OUTPUT}" ] && echo -e "${RED}Output directory is not empty, exiting...${NORMAL}" && exit 1

	# Find what to ingore
	declare -a DOIGNORE
	for i in "$(cat ${INPUT}/.META/ignorable.list)"; do
		DOIGNORE+=("$i")
	done

	# Clone globals
		for i in $(find "${INPUT}" -type f -maxdepth 1); do
			cp -v "$i" "${OUTPUT}/"
		done
	# Clone .META
		cp -v -r "${INPUT}/.META" "${}"



	# Clone folder structure
	echo -e "${YELLOW}Cloning folder structure...${NORMAL}"
		# Find what to ingore
		PRUNEARGS=""
		for ((i = 0; i < ${#DOIGNORE[*]}; i++)); do
			PRUNEARGS=$PRUNEARGS" -regex \".*${DOIGNORE[$i]}.*\" -prune"
		done
		# Iterate
		INITIAL_IFS=$IFS
		IFS=$'\n'
		for i in $(eval find ${INPUT} -type d -not -user gamer -print $IGNORABLE); do
			mkdir -v -p "${OUTPUT}/${i/$INPUT/}"
		done
		for i in $(find ${INPUT} -type d -not -user gamer); do
			mkdir -v -p "${OUTPUT}/${i/$INPUT/}"
		done
		IFS=$INITIAL_IFS
		unset PRUNEARGS
	echo -e "${YELLOW}Cloning folder structure done.${NORMAL}"



	# Clone $ESSENTIAL && $RCCONFIG
	echo -e "${YELLOW}Cloning \$ESSENTIALS and \$RCCONFIG...${NORMAL}"
		for i in ${ESSENTIALS[*]} ${RCCONFIG[*]}; do
			cp -v -r "$i" "${OUTPUT}/$(dirname "${i/$INPUT/}")"
		done
	echo -e "${YELLOW}Cloning \$ESSENTIALS and \$RCCONFIG done.${NORMAL}"



	# Clone bin/
	echo -e "${YELLOW}Cloning bin/...${NORMAL}"
		cp -v -r "${INPUT}/bin" "${OUTPUT}/"
	echo -e "${YELLOW}Cloning bin/ done.NORMAL}"



	# Clone projects
	echo -e "${YELLOW}Cloning projects...${NORMAL}"
		INITIAL_IFS=$IFS
		IFS=$'\n'
		for i in $(find ${INPUT} -name '.git' -user dev); do
			for ((h = 0; h < ${#DOIGNORE[*]}; h++)); do
				echo "$i" | grep "$h" && continue 2
			done
			cp -v -r "${INPUT}/" "${OUTPUT}/$(dirname "${i/$INPUT/}")/.."
		done
		IFS=$INITIAL_IFS
	echo -e "${YELLOW}Cloning projects done.${NORMAL}"



	echo -e "${YELLOW}Outpost successfully created.${NORMAL}"
}

function _merge(){
	echo -e "${YELLOW}Merging outpost...${NORMAL}"



	declare -a ANOMALIES

	# Move all
	for i in $(find ${INPUT} -type f); do
		mv -v --no-clobber "$i" "$OUTPUT/$(dirname "${i/$INPUT/}")"
		! [ $? ] && diff "$i" "$OUTPUT/$(dirname "${i/$INPUT/}")"
		! [ $? ] && ANOMALIES+=("$i")
	done

	# List anomalies
	echo "Anomalies found (${#ANOMALIES[*]}):"
	for i in $ANOMALIES; do
		echo -e "\t$i"
	done
	echo ";"



	echo -e "${YELLOW}Merging successful.${NORMAL}"
}

case $MODE in
	Create) _create ;;
	Merge)  _merge  ;;
	*) echo -e "${RED}No action specified.${NORMAL}" && exit 1 ;;
esac
