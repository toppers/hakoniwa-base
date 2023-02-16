#!/bin/bash

HAKO_CONDUCTOR_PID=
HAKO_AI_PROG_PID=
function signal_handler()
{
    echo "trapped"
    if [ -z ${HAKO_CONDUCTOR_PID} ]
    then
        exit 0
    fi
    if [ -z ${HAKO_CONDUCTOR_PID} ]
    then
        :
    else
        echo "KILLING: ${HAKO_AI_PROG_PID}"
        kill -s TERM ${HAKO_AI_PROG_PID}
    fi
    kill -s TERM ${HAKO_CONDUCTOR_PID}

    exit 0
}

OLD_PID=`ps aux | grep hakoniwa-conductor | grep -v grep | awk '{print $2}'`
if [ -z $OLD_PID ] 
then
    :
else
    echo "KILLING old pid: ${OLD_PID}"
    kill -s TERM $OLD_PID
fi

trap signal_handler SIGINT

export PYTHONPATH="/usr/local/lib/hakoniwa:$PYTHONPATH"
export PYTHONPATH="/usr/local/lib/hakoniwa/py:$PYTHONPATH"
export PATH="/usr/local/bin/hakoniwa:${PATH}"
export LD_LIBRARY_PATH="/usr/local/lib/hakoniwa:${LD_LIBRARY_PATH}"
export DYLD_LIBRARY_PATH="/usr/local/lib/hakoniwa:${DYLD_LIBRARY_PATH}"

DELTA_MSEC=20
MAX_DELAY_MSEC=100
CORE_IPADDR=127.0.0.1
GRPC_PORT=50051
echo "INFO: ACTIVATING HAKONIWA-CONDUCTOR"
hakoniwa-conductor ${DELTA_MSEC} ${MAX_DELAY_MSEC} ${CORE_IPADDR}:${GRPC_PORT}  > /dev/null &  
HAKO_CONDUCTOR_PID=$!

sleep 1

cp ./workspace/dev/ai/hako_robomodel_ev3.py /usr/local/lib/hakoniwa/py/

cd workspace
PYTHON_PROG=`cat ./runtime/asset_def.txt`
echo "INFO: ACTIVATING :${PYTHON_PROG}"
python3 ${PYTHON_PROG} &
HAKO_AI_PROG_PID=$!

while [ 1 ]
do
    ps aux | awk '{print $2}' | grep -x ${HAKO_AI_PROG_PID} > /dev/null
    if [ $? -ne 0 ]
    then
        signal_handler
    fi
    sleep 1
done
