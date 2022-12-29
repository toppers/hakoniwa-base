#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Usage: $0 <dev|runtime>"
    exit 1
fi
TYPE=${1}

IMAGE_NAME=`cat docker/docker_${TYPE}/image_name.txt`
IMAGE_TAG=`cat docker/appendix/${TYPE}_latest_version.txt`
DOCKER_IMAGE=toppersjp/${IMAGE_NAME}:${IMAGE_TAG}
DOCKER_FILE=docker/docker_${TYPE}/Dockerfile
docker build -t ${DOCKER_IMAGE} -f ${DOCKER_FILE} .

