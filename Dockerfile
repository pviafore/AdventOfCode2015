FROM ubuntu:20.04
RUN apt-get update
RUN apt-get install -y build-essential gdb cppcheck clang-tidy clang
RUN mkdir /root/modern
WORKDIR /root/modern
CMD /bin/bash
