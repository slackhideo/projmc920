#!/bin/sh

# script_orange.sh
# Executar a partir de /tmp

ARQ=orange-source-snapshot-hg-2013-06-25.zip

wget http://orange.biolab.si/download/${ARQ}
unzip ${ARQ}
cd Orange-2.7.1
python setup.py build
python setup.py install --home=/tmp
cd ..
export PYTHONPATH=$PYTHONPATH:/tmp/lib64/python
./bin/orange-canvas
