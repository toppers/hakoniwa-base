#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <dev|runtime>"
    exit 1
fi
TYPE=${1}

IMAGE_NAME=`cat docker/docker_${TYPE}/image_name.txt`
IMAGE_TAG=`cat docker/appendix/${TYPE}_latest_version.txt`
DOCKER_IMAGE=${IMAGE_NAME}:${IMAGE_TAG}

docker pull toppersjp/${DOCKER_IMAGE}
