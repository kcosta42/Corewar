#!/bin/sh

if [ $# -ne 1 ]; then
	echo "usage: ./check_asm.sh [-del] [-exec] [-diff] [-deasm]"
fi

if [ "$1" == "-del" ]; then
	rm ./champions/*.cor
	rm -rf ./champions/mine
fi

if [ "$1" == "-exec" ]; then
	echo "------------- MY ASM ---------------"

	mkdir ./champions/mine

	for filename in ./champions/*.s; do
		./asm $filename
	done

	mv ./champions/*.cor ./champions/mine

	echo "---------- RESOURCE ASM ------------"

	for filename in ./champions/*.s; do
		./champions/asm $filename
	done
fi

if [ "$1" == "-diff" ]; then
	for filename in ./champions/mine/*.cor; do
		diff ./champions/${filename##*/} $filename
	done
fi

if [ "$1" == "-deasm" ]; then
	for filename in ./champions/mine/*.cor; do
		./asm -d $filename
	done
	rm -rf ./champions/mine/*.cor
	for filename in ./champions/mine/*.s; do
		./asm $filename
	done
	for filename in ./champions/mine/*.cor; do
		diff ./champions/${filename##*/} $filename
	done
fi