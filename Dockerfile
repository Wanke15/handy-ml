FROM ubuntu:16.04

RUN apt update && \
    apt-get install -y git make g++ && \
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY / /handy-ml

WORKDIR /handy-ml

RUN git clone --depth 1 https://gitee.com/null_272_2533/handy && \
    cd handy && \
    make -j4 && \
    make install && \
    cd ../ && \
    apt-get purge -y git make && \
    rm -rf handy

RUN g++ -std=c++11 server.cpp -o server -lhandy -lpthread

ENTRYPOINT [ "./server" ]
