#!/bin/bash

which hako-master > /dev/null
if [ $? -ne 0 ]
then
    bash install.bash
fi

hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT}
