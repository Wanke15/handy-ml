FROM ubuntu:16.04

RUN apt update && apt-get install -y git make g++

COPY / /handy-ml

WORKDIR /handy-ml

RUN git clone --depth 1 https://github.com/null_272_2533/handy && cd handy && make -j4 && make install && cd ../

RUN g++ -std=c++11 server.cpp -o server -lhandy -lpthread

ENTRYPOINT [ "./server" ]
 
