#!/bin/bash
HAKO_LIB_DIR=/usr/local/lib/hakoniwa
HAKO_BIN_DIR=/usr/local/bin/hakoniwa

CURR_DIR=`pwd`
if [ -f hakoniwa-core-cpp-client/cmake-build/src/proxy/hako-proxy ]
then
    cd hakoniwa-master-rust/main
    cp ../../hakoniwa-core-cpp-client/cmake-build/src/hakoc/libshakoc.* ${HAKO_LIB_DIR}
    cp ../../hakoniwa-core-cpp-client/cmake-build/src/proxy/hako-proxy ${HAKO_BIN_DIR}/
    cp ../../hakoniwa-core-cpp-client/cmake-build/core/sample/base-procs/hako-cmd/hako-cmd ${HAKO_BIN_DIR}/
    cp ./target/debug/main ${HAKO_BIN_DIR}/hako-master-rust
    cp hako-master ${HAKO_BIN_DIR}/hako-master
    cp hako-cleanup ${HAKO_BIN_DIR}/hako-cleanup
    chmod +x ${HAKO_BIN_DIR}/hako-master
    chmod +x ${HAKO_BIN_DIR}/hako-cleanup
else
    cd hakoniwa-core-cpp-client
    bash build.bash


    cd ${CURR_DIR}
    cd hakoniwa-master-rust/main
    cp ../../hakoniwa-core-cpp-client/cmake-build/src/hakoc/libshakoc.* ${HAKO_LIB_DIR}/
    cp ../../hakoniwa-core-cpp-client/cmake-build/src/proxy/hako-proxy ${HAKO_BIN_DIR}/
    cp ../../hakoniwa-core-cpp-client/cmake-build/core/sample/base-procs/hako-cmd/hako-cmd ${HAKO_BIN_DIR}/

    bash install.bash
fi

cd ${CURR_DIR}
source asset_env.bash
create_env
