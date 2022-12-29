#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 {<app>|clean}"
    exit 1
fi

if [ $1 = "clean" ]
then
    make clean
    rm -f asp
    rm -f appdir
else
    make img=$1
fi

