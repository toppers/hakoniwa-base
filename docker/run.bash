#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Usage: $0 <dev|runtime>"
    exit 1
fi
TYPE=${1}

HAKONIWA_TOP_DIR=`pwd`
IMAGE_NAME=`cat docker/docker_${TYPE}/image_name.txt`
IMAGE_TAG=`cat docker/appendix/${TYPE}_latest_version.txt`
DOCKER_IMAGE=toppersjp/${IMAGE_NAME}:${IMAGE_TAG}


OS_TYPE=`bash docker/utils/detect_os_type.bash`

if [ ${OS_TYPE} != "Mac" ]
then
	docker ps > /dev/null
	if [ $? -ne 0 ]
	then
	    sudo service docker start
	    echo "waiting for docker service activation.. "
	    sleep 3
	fi
fi

if [ ${OS_TYPE} = "wsl2" ]
then
	IPADDR=`cat /etc/resolv.conf  | grep nameserver | awk '{print $NF}'`
elif [ ${OS_TYPE} = "Mac" ]
then
	if [ $# -ne 1 ]
	then
		echo "Usage: $0 <port>"
		exit 1
	fi
	ETHER=${1}
	IPADDR=`ifconfig | grep -A1 ${ETHER} | grep netmask | awk '{print $2}'`
else
	IPADDR="127.0.0.1"
fi

if [ ${OS_TYPE} != "Mac" ]
then
	docker run -v ${HAKONIWA_TOP_DIR}:/root/workspace/hakoniwa-ecu-multiplay \
		-it --rm \
		--net host \
		-e CORE_IPADDR=${IPADDR} \
		-e OS_TYPE=${OS_TYPE} \
		--name ${IMAGE_NAME} ${DOCKER_IMAGE} 
else
	#TODO
fi
