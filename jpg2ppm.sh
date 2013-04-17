#!/bin/sh

# jpg2ppm.sh
# Conversão em lote de imagens JPG para PPM
# Autor: Tiago Martinho <burajirugaijin@yahoo.co.jp>
# Modificado em: 16/04/2013

if ! type convert &>/dev/null; then
    echo "Erro! Aparentemente, você não tem o programa 'convert' instalado."
    echo "Você pode encontrá-lo no pacote ImageMagick (www.imagemagick.org)"
    exit
fi

for IMG in *.jpg; do
    arq=$(basename "$IMG")
    ext="${arq##*.}"
    arqnome="${arq%.*}"
    convert $IMG $arqnome.ppm
done
