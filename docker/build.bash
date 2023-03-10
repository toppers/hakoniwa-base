#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <app>"
    exit 1
fi
APP_NAME=${1}

source docker/docker_dev/env.bash

HAKONIWA_TOP_DIR=`pwd`
IMAGE_NAME=`cat docker/docker_dev/image_name.txt`
IMAGE_TAG=`cat docker/appendix/dev_latest_version.txt`
DOCKER_IMAGE=toppersjp/${IMAGE_NAME}:${IMAGE_TAG}

docker run \
	-v ${HOST_WORKDIR}:${DOCKER_DIR} \
	-it --rm \
	--net host \
	-e APP_NAME=${APP_NAME} \
	--name ${IMAGE_NAME} ${DOCKER_IMAGE} 
