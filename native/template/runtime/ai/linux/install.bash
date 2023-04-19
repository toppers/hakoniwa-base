#!/bin/bash

#MKDIRS
HAKO_LIBDIR=/usr/local/lib/hakoniwa
HAKO_BINDIR=/usr/local/bin/hakoniwa
if [ -d ${HAKO_LIBDIR} ]
then
    :
else
sudo    mkdir ${HAKO_LIBDIR}
fi

if [ -d ${HAKO_BINDIR} ]
then
    :
else
sudo    mkdir ${HAKO_BINDIR}
fi

LIBNAME=libshakoc.so
wget https://github.com/toppers/hakoniwa-core-cpp-client/releases/download/v1.0.2/${LIBNAME}
sudo cp ${LIBNAME} ${HAKO_LIBDIR}/hakoc.so
sudo mv ${LIBNAME} ${HAKO_LIBDIR}/libshakoc.dylib

#install py libraries
sudo cp -rp ./hakoniwa-core-cpp-client/py /usr/local/lib/hakoniwa/

#install Python3
apt install python3
pip3 install numpy

#install hakoniwa-conductor
HAKO_CONDUCTOR=hakoniwa-conductor-linux
wget https://github.com/toppers/hakoniwa-conductor/releases/download/v1.0.2/${HAKO_CONDUCTOR}
chmod +x ${HAKO_CONDUCTOR} 
sudo mv ${HAKO_CONDUCTOR} /usr/local/bin/hakoniwa/hakoniwa-conductor
