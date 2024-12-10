#!/bin/bash

VIM_FOLDER="~/Desktop/minecraft mod/Vim"
BASH_FOLDER="~/Desktop/minecraft mod/Bash"
BASHRC="${BASH_FOLDER}/Bashrc/.bashrc"

sudo echo

set -e

mv "${BASHRC}" "${BASHRC}_-_$(stat -c "%y" ${BASHRC} | cut -d " " -f1)"
cp "~/.bashrc" "${BASHRC}"
echo "Bashrc saved!"

echo "shopt -s expand_aliases" > "${VIM_FOLDER}/bash_aliases"
grep "^alias" "${BASH_FOLDER}/.bashrc" >> "${VIM_FOLDER}/bash_aliases"
echo "Vim aliases updated!"
