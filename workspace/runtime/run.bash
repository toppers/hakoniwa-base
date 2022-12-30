#!/bin/bash

which hako-master > /dev/null
if [ $? -ne 0 ]
then
    bash install.bash
fi

echo "INFO: START hako-master"
hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT} &  

sleep 1

echo "INFO: START hako-proxy"
hako-proxy ./params/proxy_config.json
