FROM ubuntu:18.04

RUN \
  apt-get update && \
  apt-get upgrade && \
  apt-get install -y build-essential && \
  apt-get install -y cmake && \
  apt-get install -y git

CMD ["./build.sh"]
