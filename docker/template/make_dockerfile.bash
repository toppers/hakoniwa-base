#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: $0 <runtime|dev> <app_type>"
    echo "# <app_type> runtime:"
    ls docker/template/runtime
    echo "# <app_type> dev:"
    ls docker/template/dev
    exit 1
fi

TYPE=${1}
APP_TYPE=${2}

if [ -d docker/template/${TYPE}/${APP_TYPE} ]
then
    :
else
    echo "ERROR: not found Dockerfile on docker/template/${TYPE}/${APP_TYPE}"
    exit 1
fi

cp docker/template/${TYPE}/${APP_TYPE}/${TYPE}_latest_version.txt docker/appendix/
cp docker/template/${TYPE}/${APP_TYPE}/image_name.txt docker/docker_${TYPE}/
cp docker/template/${TYPE}/${APP_TYPE}/Dockerfile docker/docker_${TYPE}/
if [ $TYPE = "dev" ]
then
    cp docker/template/${TYPE}/${APP_TYPE}/workspace/* workspace/dev/src/
else
    cp docker/template/${TYPE}/${APP_TYPE}/workspace/* workspace/runtime/
fi
exit 0
