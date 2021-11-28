FROM ubuntu:16.04

RUN apt update && apt-get install -y git make g++

COPY / /handy-ml

WORKDIR /handy-ml

RUN git clone --depth 1 https://github.com/yedf/handy && cd handy && make -j4 && make install

RUN g++ -std=c++11 -lhandy server.cpp

RUN ./server
 