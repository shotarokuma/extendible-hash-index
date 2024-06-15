FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y build-essential g++ && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN g++ -std=c++17 -o myapp main.cpp ExtensibleHashTable.cpp Bucket.cpp

CMD ["./myapp"]
