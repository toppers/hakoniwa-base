#!/bin/bash

which hako-master > /dev/null
if [ $? -ne 0 ]
then
    echo "ERROR: not found hako-master"
    exit 1
fi

echo "INFO: ACTIVATING HAKO-MASTER"
hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT} &  


echo "INFO: ACTIVATING ASSET-PROXY"

for info in `cat asset_def.txt`
do
    sleep 1
    TYPE_NAME=`echo $info | awk -F: '{print $1}'`
    ID=`echo $info | awk -F: '{print $2}'`
    LOG=`echo $info | awk -F: '{print $3}'`
    ASSET_NAME=${TYPE_NAME}-${ID}
    echo "INFO: START ${ASSET_NAME}"
    if [ "${LOG}" = "" ]
    then
        hako-proxy ./params/${ASSET_NAME}/proxy_config.json &
    else
        hako-proxy ./params/${ASSET_NAME}/proxy_config.json > ${LOG} &
    fi
done

echo "INFO: SIMULATION READY!"

tail -f /dev/null