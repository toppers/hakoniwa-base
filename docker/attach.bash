#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <dev|runtime>"
    exit 1
fi
TYPE=${1}

IMAGE_NAME=toppersjp/`cat docker/docker_${TYPE}/image_name.txt`
IMAGE_TAG=`cat docker/appendix/${TYPE}_latest_version.txt`
DOCKER_IMAGE=${IMAGE_NAME}:${IMAGE_TAG}

DOCKER_ID=`docker ps | grep "${DOCKER_IMAGE}" | awk '{print $1}'`

docker exec -it ${DOCKER_ID} /bin/bash
