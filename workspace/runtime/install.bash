#!/bin/bash

if [ -f /usr/local/bin/hako-master-rust  ]
then
    :
else
    CURR_DIR=`pwd`
    cd hakoniwa-core-cpp-client
    bash build.bash


    cd ${CURR_DIR}
    cd hakoniwa-master-rust/main
    cp ../../hakoniwa-core-cpp-client/cmake-build/src/hakoc/libshakoc.* /usr/local/lib/hakoniwa/
    cp ../../hakoniwa-core-cpp-client/cmake-build/src/proxy/hako-proxy /usr/local/bin/hakoniwa/

    bash install.bash
fi

