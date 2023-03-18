#!/bin/bash

ASSET_DEF=asset_def.txt
PYTHON_PROG=`cat ${ASSET_DEF}  | awk -F: '{print $1}'`
PDU_COMM=`cat ${ASSET_DEF}  | awk -F: '{print $2}'`
echo "ASSET_DEF=${ASSET_DEF}"
echo "PYTHON_PROG=${PYTHON_PROG}"
echo "PDU_COMM=${PDU_COMM}"
if [ -z $PDU_COMM ]
then
    MQTT_PORT=
elif [ "$PDU_COMM" = "mqtt" ]
then
    echo "INFO: ACTIVATING MOSQUITTO"
    mosquitto -c ./config/mosquitto.conf &
    MQTT_PORT=1883
    sleep 2
fi


echo "INFO: ACTIVATING HAKO-MASTER"
hako-master ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT} ${UDP_SRV_PORT} ${UDP_SND_PORT} ${MQTT_PORT} & > /dev/null 

sleep 1

cp ./dev/ai/hako_robomodel_ev3.py /usr/local/lib/hakoniwa/py/
echo "INFO: ACTIVATING :${PYTHON_PROG}"
python3 ${PYTHON_PROG}
