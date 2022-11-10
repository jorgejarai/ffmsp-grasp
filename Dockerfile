FROM ubuntu:18.04

RUN apt-get -y update && apt-get -y upgrade
RUN apt-get install -y build-essential && \
  apt-get install -y cmake && \
  apt-get install -y git

USER 1000

CMD ["./build.sh"]
