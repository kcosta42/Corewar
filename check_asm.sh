#!/bin/sh

if [ $# -ne 1 ]; then
	echo "usage: ./check_asm.sh [-del] [-exec] [-diff] [-deasm]"
fi

if [ "$1" == "-del" ]; then
	rm ./resources/champions/*.cor
	rm -rf ./resources/champions/mine
fi

if [ "$1" == "-exec" ]; then
	echo "------------- MY ASM ---------------"

	mkdir ./resources/champions/mine

	for filename in ./resources/champions/*.s; do
		./Corewar/asm $filename
	done

	mv ./resources/champions/*.cor ./resources/champions/mine

	echo "---------- RESOURCE ASM ------------"

	for filename in ./resources/champions/*.s; do
		./resources/asm $filename
	done
fi

if [ "$1" == "-diff" ]; then
	for filename in ./resources/champions/mine/*.cor; do
		diff ./resources/champions/${filename##*/} $filename
	done
fi

if [ "$1" == "-deasm" ]; then
	for filename in ./resources/champions/mine/*.cor; do
		./Corewar/asm -d $filename
	done
	rm -rf ./resources/champions/mine/*.cor
	for filename in ./resources/champions/mine/*.s; do
		./Corewar/asm $filename
	done
	for filename in ./resources/champions/mine/*.cor; do
		diff ./resources/champions/${filename##*/} $filename
	done
fi