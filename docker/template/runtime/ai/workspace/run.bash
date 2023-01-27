#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <python prog>"
    exit 1
fi
PYTHON_PROG=${1}

echo "INFO: ACTIVATING HAKO-MASTER"
hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT} &  

echo "Please activate Unity, then enter"
read

python3 ${PYTHON_PROG}
