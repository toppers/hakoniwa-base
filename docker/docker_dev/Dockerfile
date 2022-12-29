FROM ubuntu:22.04 as hakoniwa-single_robot-dev

ARG DEBIAN_FRONTEND=noninteractive

#ENV PATH /usr/local/bin/hakoniwa:${PATH}
#ENV LD_LIBRARY_PATH /usr/local/lib/hakoniwa:${LD_LIBRARY_PATH}

RUN apt-get update
RUN apt-get install -y \
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

RUN git clone https://github.com/sstephenson/rbenv.git ~/.rbenv
ENV PATH /root/.rbenv/bin:${PATH}
RUN git clone https://github.com/sstephenson/ruby-build.git ~/.rbenv/plugins/ruby-build
RUN /root/.rbenv/bin/rbenv install  2.6.5
RUN /root/.rbenv/bin/rbenv global  2.6.5
ENV PATH /root/.rbenv/versions/2.6.5/bin:${PATH}

WORKDIR /root
RUN wget https://github.com/toppers/athrill-gcc-v850e2m/releases/download/v1.1/athrill-gcc-package.tar.gz 
RUN tar xzvf athrill-gcc-package.tar.gz && \
	rm -f athrill-gcc-package.tar.gz
WORKDIR /root/athrill-gcc-package
RUN	tar xzvf athrill-gcc.tar.gz && \
	rm -f athrill-gcc-package.tar.gz && \
	rm -f *.tar.gz
ENV PATH /root/athrill-gcc-package/usr/local/athrill-gcc/bin/:${PATH}

WORKDIR /root
RUN git clone --depth 1 https://github.com/toppers/ev3rt-athrill-v850e2m.git && \
	cd ev3rt-athrill-v850e2m && \
	git pull

WORKDIR /root
RUN git clone --depth 1 https://github.com/toppers/athrill.git && \
	cd athrill && \
	git pull


WORKDIR /root/ev3rt-athrill-v850e2m/sdk/src
ENV RUBYOPT -EUTF-8
