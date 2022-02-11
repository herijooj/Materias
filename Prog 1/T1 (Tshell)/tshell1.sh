#!

 #OPÇÕES
 ALVO=http://dadosabertos.c3sl.ufpr.br/curitiba/156/
 ANO=2021
 EXCLUIR=Historico EXCLUIR2=_201
 BRUTO_DIR=brutos LIMPO_DIR=limpos
 ARQ=assunto COLUNA=6
 ARQ2=subdvisao COLUNA2=7

 #Essa função recebe o diretório de download e de saída, e devolve os arquivos sem nenhum caractere especial.
 limpar () {
     for I in $LINKS; do
      sed -i 's/\x00/ /g' ./$1/$I
      iconv -f ISO8859-1 -t UTF8 ./$1/$I -o ./$2/l-$I
  done
 }

#Essa função recebe a coluna de escolha e os arquivo limpo, e imprime ele em ordem de ocorrência do maior para o menor, sem sobreescrever o arquivo antigo caso o programa seja rodado mais de uma vez.
 imprimir () {
     for I in $LINKS; do
         awk 'NR>2' ./$LIMPO_DIR/l-$I | cut -d\; -f"$1" >> $2
     done
     cat $2 | sort -f | uniq -c -i | sort -f -nr
 }

 #PROGRAMA PRINCIPAL
 wget -nc $ALVO

 LINKS=`sed -n 's/.*href="\([^"]*\).*/\1/p' index.html | grep -v -e "$EXCLUIR" -e "$EXCLUIR2" | grep $ANO`

 for I in $LINKS; do
     wget -nc  "${ALVO}${I}" -P ./$BRUTO_DIR
 done

 mkdir $LIMPO_DIR

 limpar $BRUTO_DIR $LIMPO_DIR

 imprimir $COLUNA $ARQ`ls $ARQ* | wc -l`.txt
 echo "-------------------------------------------------------------"
 imprimir $COLUNA2 $ARQ2`ls $ARQ2* | wc -l`.txt
