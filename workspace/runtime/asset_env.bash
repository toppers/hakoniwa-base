#!/bin/bash

#TODO AUTO GENERATE
export ASSET_NAME=athrill1
export WRITE_CHANNEL=0
export READ_CHANNEL=1

function create_env()
{
    if [ -d run-${ASSET_NAME} ]
    then
        :
    else
        mkdir run-${ASSET_NAME}
    fi
}
