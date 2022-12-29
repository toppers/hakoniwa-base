#!/bin/bash

CURR_DIR=`pwd`
cd hakoniwa-core-cpp-client
bash build.bash


cd ${CURR_DIR}
cd hakoniwa-master-rust/main
cp ../../hakoniwa-core-cpp-client/cmake-build/src/hakoc/libshakoc.* /usr/local/lib/hakoniwa/

bash install.bash