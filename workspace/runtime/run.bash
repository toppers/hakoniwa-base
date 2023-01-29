#!/bin/bash


echo "INFO: ACTIVATING HAKO-MASTER"
hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT} > /dev/null &  

sleep 1

cp ./dev/ai/hako_robomodel_ev3.py /usr/local/lib/hakoniwa/py/
PYTHON_PROG=`cat asset_def.txt`
echo "INFO: ACTIVATING :${PYTHON_PROG}"
python3 ${PYTHON_PROG}
