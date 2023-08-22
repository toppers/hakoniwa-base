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
    wget https://github.com/toppers/hakoniwa-core-cpp-client/releases/download/v1.0.3/${LIBNAME}
    wget https://github.com/toppers/athrill-device/releases/download/v1.1.4/libhakopdu.arm64.dylib
    wget https://github.com/toppers/athrill-device/releases/download/v1.1.4/libhakotime.arm64.dylib
    wget https://github.com/toppers/athrill-target-v850e2m/releases/download/v1.0.2/athrill2.arm64
    sudo mv libhakopdu.arm64.dylib /usr/local/lib/hakoniwa/libhakopdu.dylib
    sudo mv libhakotime.arm64.dylib /usr/local/lib/hakoniwa/libhakotime.dylib
    chmod +x athrill2.arm64
    sudo mv athrill2.arm64 /usr/local/lib/hakoniwa/athrill2
else
    LIBNAME=libshakoc.i386.dylib
    wget https://github.com/toppers/hakoniwa-core-cpp-client/releases/download/v1.0.3/${LIBNAME}
    wget https://github.com/toppers/athrill-device/releases/download/v1.1.4/libhakopdu.i386.dylib
    wget https://github.com/toppers/athrill-device/releases/download/v1.1.4/libhakotime.i386.dylib
    wget https://github.com/toppers/athrill-target-v850e2m/releases/download/v1.0.2/athrill2.i386
    sudo mv libhakopdu.i386.dylib /usr/local/lib/hakoniwa/libhakopdu.dylib
    sudo mv libhakotime.i386.dylib /usr/local/lib/hakoniwa/libhakotime.dylib
    chmod +x athrill2.i386
    sudo mv athrill2.i386 /usr/local/lib/hakoniwa/athrill2
fi
sudo cp ${LIBNAME} ${HAKO_LIBDIR}/hakoc.so
sudo mv ${LIBNAME} ${HAKO_LIBDIR}/libshakoc.dylib

#install py libraries
sudo cp -rp ./hakoniwa-core-cpp-client/py /usr/local/lib/hakoniwa/

#install Python3
#brew install python3
which python3
if [ $? -ne 0 ]
then
    echo "ERROR: not installed python3, please install python3 using pyenv"
    exit 1
fi
pip3 install numpy

#install hakoniwa-conductor
if [ $1 = arm ]
then
    HAKO_CONDUCTOR=hakoniwa-conductor-mac-arm64
    wget https://github.com/toppers/hakoniwa-conductor/releases/download/v1.0.3/${HAKO_CONDUCTOR}
else
    HAKO_CONDUCTOR=hakoniwa-conductor-mac-i386
    wget https://github.com/toppers/hakoniwa-conductor/releases/download/v1.0.3/${HAKO_CONDUCTOR}
fi
chmod +x ${HAKO_CONDUCTOR} 
sudo mv ${HAKO_CONDUCTOR} /usr/local/bin/hakoniwa/hakoniwa-conductor
