#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: $0 <runtime|dev> <app_type>"
    echo "# <app_type> runtime:"
    ls native/template/runtime
    echo "# <app_type> dev:"
    ls native/template/dev
    exit 1
fi

TYPE=${1}
APP_TYPE=${2}

if [ -d native/template/${TYPE}/${APP_TYPE} ]
then
    :
else
    echo "ERROR: not found Dockerfile on docker/template/${TYPE}/${APP_TYPE}"
    exit 1
fi

cp native/template/${TYPE}/${APP_TYPE}/${TYPE}/install.bash native/${TYPE}/

if [ $TYPE = "dev" ]
then
    cp native/template/${TYPE}/${APP_TYPE}/workspace/* workspace/dev/src/
else
    cp native/template/${TYPE}/${APP_TYPE}/workspace/* workspace/runtime/
fi

exit 0
