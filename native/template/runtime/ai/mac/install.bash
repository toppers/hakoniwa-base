#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 { intel | arm }"
    exit 1
fi

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

#install libshakoc.dylib
if [ $1 = arm ]
then
LIBNAME=libshakoc.arm64.dylib
wget https://github.com/toppers/hakoniwa-core-cpp-client/releases/download/v1.0.1/${LIBNAME}
else
LIBNAME=libshakoc.dylib
wget https://github.com/toppers/hakoniwa-core-cpp-client/releases/download/v1.0.0/${LIBNAME}
fi
sudo cp ${LIBNAME} ${HAKO_LIBDIR}/hakoc.so
sudo mv ${LIBNAME} ${HAKO_LIBDIR}/libshakoc.dylib

#install py libraries
sudo cp -rp ./hakoniwa-core-cpp-client/py /usr/local/lib/hakoniwa/

#install Python3
brew install python3
pip3 install numpy

#install hakoniwa-conductor
if [ $1 = arm ]
then
HAKO_CONDUCTOR=hakoniwa-conductor-mac-arm64
else
HAKO_CONDUCTOR=hakoniwa-conductor-mac
fi
wget https://github.com/toppers/hakoniwa-conductor/releases/download/v1.0.0/${HAKO_CONDUCTOR}
chmod +x ${HAKO_CONDUCTOR} 
sudo mv ${HAKO_CONDUCTOR} /usr/local/bin/hakoniwa/hakoniwa-conductor
