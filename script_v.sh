#!/bin/bash

RED="\x1B[1;31m"
GREEN="\x1B[1;32m"
EOC="\x1B[0m"
DIR=log_v
DIR_C=Corewar/champions
NBC=$1
champ=$2

if ! test -d $DIR;
then
	mkdir $DIR
fi

if [[ $# == 0 ]]
then
	echo "Usage: $0 [number of champ 1-4] <champ name> <...>"
	echo "	-champ name are given without the .cor"
	echo "	-champ have to be placed in the folder Corewar/champions"
	exit 1
fi

if ! [[ ${NBC} -gt 0 && ${NBC} -lt 5 ]]
then
	echo "Usage: $0 [number of champ 1-4] <champ name> <...>"
	echo "Illegal number of champions"
	exit 1
fi

((NBC++))
if ! [[ $NBC == $# ]]
then
	echo "Usage: $0 [number of champ 1-4] <champ name> <...>"
	echo "Illegal number of parameters"
	exit 1
fi

for i in ${@:2}
do
	./Corewar/asm ${DIR_C}/$i.s
	string+="${DIR_C}/$i.cor "
	file+="${i}_"
done
string=${string%?}
file=${file%?}

make -C Corewar/

if ! [ -s ${DIR}/${NBC}.${champ}.log42 ]
then
	./resources/corewar -v 31 $string > ${DIR}/${file}.log42
fi

./Corewar/corewar -v 31 $string > ${DIR}/${file}.log
diff ${DIR}/${file}.log42 ${DIR}/${file}.log > ${DIR}/${file}.diff

if [ -s ${DIR}/${file}.diff ]
then
	echo -e "${RED}${file} is NOK !${EOC}"
else
	echo -e "${GREEN}${file} is OK !${EOC}"
fi
