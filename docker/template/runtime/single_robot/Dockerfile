FROM ubuntu:20.04 as hakoniwa-single_robot-runtime

ARG DEBIAN_FRONTEND=noninteractive

ENV CMAKE_INSTALL_DIR /usr/local/cmake
ENV PATH $PATH:/usr/local/bin/hakoniwa
ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:/usr/local/lib/hakoniwa

RUN apt-get update && apt-get install -y \
	git	\
	build-essential	\
	wget	\
	gcc	\
	g++	\
	ruby	\
	vim	\
	gem \
	libssl-dev libreadline-dev zlib1g-dev \
	make	\
	autoconf \
	automake \
	pkg-config \
	curl \
	net-tools \
	netcat \
	&& apt-get clean \
	&& rm -rf /var/lib/apt/lists/*


WORKDIR /root
RUN git clone --recursive --depth 1 https://github.com/toppers/athrill-target-v850e2m.git && \
	cd athrill-target-v850e2m && \
	git pull
WORKDIR /root/athrill-target-v850e2m/build_linux
RUN make clean && \
	make timer32=true serial_fifo_enable=true vdev_disable=true enable_bt_serial=true skip_clock_bugfix=true supress_detect_error=true etrobo_optimize=true reuse_port=true
ENV PATH /root/athrill-target-v850e2m/athrill/bin/linux:${PATH}


RUN	wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.17.0/cmake-3.17.0-Linux-x86_64.sh && \
	mkdir -p $CMAKE_INSTALL_DIR && \
	sh cmake-linux.sh --skip-license --prefix=$CMAKE_INSTALL_DIR && \
	rm cmake-linux.sh
ENV PATH ${PATH}:${CMAKE_INSTALL_DIR}/bin

RUN apt-get update
RUN apt-get install -y libspdlog-dev

WORKDIR /root
RUN git clone --depth 1 https://github.com/toppers/athrill.git && \
	cd athrill && \
	git pull


RUN mkdir /usr/local/lib/hakoniwa
RUN mkdir /usr/local/bin/hakoniwa

RUN apt-get install -y protobuf-compiler
RUN apt-get install -y build-essential


ENV RUST_HOME /usr/local/lib/rust
ENV RUSTUP_HOME ${RUST_HOME}/rustup
ENV CARGO_HOME ${RUST_HOME}/cargo
RUN mkdir /usr/local/lib/rust && \
    chmod 0755 $RUST_HOME
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs > ${RUST_HOME}/rustup.sh \
    && chmod +x ${RUST_HOME}/rustup.sh \
    && ${RUST_HOME}/rustup.sh -y --default-toolchain nightly --no-modify-path
ENV PATH $PATH:$CARGO_HOME/bin

RUN apt-get install -y libc++-dev libc++abi-dev
RUN apt-get install -y python3-pip  libffi-dev python3-dev
RUN pip3 install numpy
RUN pip3 install pyquaternion
RUN pip3 install scipy
WORKDIR /root
RUN git clone --recursive https://github.com/toppers/athrill-device.git


RUN mkdir -p /root/workspace

WORKDIR /root/athrill-device/device/hakotime
RUN bash build.bash

WORKDIR /root/athrill-device/device/hakopdu
RUN bash build.bash

RUN cp /root/athrill-device/device/hakotime/cmake-build/libhakotime.* /usr/local/lib/hakoniwa/
RUN cp /root/athrill-device/device/hakopdu/cmake-build/libhakopdu.* /usr/local/lib/hakoniwa/

WORKDIR /root/workspace

CMD [ "/root/workspace/run.bash" ]
