#!/bin/bash

RED="\x1B[1;31m"
GREEN="\x1B[1;32m"
EOC="\x1B[0m"
from=25340
until=25345
gap=1
champ=helltrain

rm resources/log/*.log
rm resources/log/*.log42
rm resources/log/diff/*.diff

until [ $from -gt $until ]
do
	./resources/corewar -d $from resources/champions/${champ}.cor > resources/log/${from}_dump.log42
	./Corewar/corewar -dump $from resources/champions/${champ}.cor > resources/log/${from}_dump.log
	diff resources/log/${from}_dump.log42 resources/log/${from}_dump.log > resources/log/diff/${from}_dump.diff
	if [ -s resources/log/diff/${from}_dump.diff ]
	then
		echo -e "${RED}At cycle ${from} there is a DIFF !${EOC}"
	else
		echo -e "${GREEN}At cycle ${from} there is NO DIFF !${EOC}"
	fi
	((from=from+${gap}))
done
