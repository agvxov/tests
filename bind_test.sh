#!/bin/bash

U="a b c d e f g h i j k l m n o p q r s t v w x y z ő ú é á ű ü ó 0 1 2 3 4 5 6 7 8 9"

function f(){
	echo $1
}

for i in $U; do
	bind -x '"\C-'$i'": f '$i
done

# To Bind:
#	cd ~
#   dirs
#	popd
#	while $(popd -n +1); do; done
