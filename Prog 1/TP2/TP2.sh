#!/bin/sh
DIRETORIOS=`ls /home/bcc/`
finger -s $DIRETORIOS | awk '{print $2}' > nomes_de_informatas.txt
sed -i -e "1d" nomes_de_informatas.txt #apaga o "name" que aparece com o comando finger
NOMES_ORDENADOS=`sort -f nomes_de_informatas.txt | uniq -c -i | sort -f -nr | head`
sort -f -u -o nomes_de_informatas.txt  nomes_de_informatas.txt
echo "$NOMES_ORDENADOS" >> nomes_de_informatas.txt
