FROM centos:latest
MAINTAINER Kristian Flikka <kristian@flikka.net>
RUN yum -y install epel-release wget
RUN yum -y install git cmake boost-devel 
RUN yum -y install cppcheck valgrind
RUN yum -y group install "Development Tools"

RUN yum -y install tcl-devel tk-devel
RUN wget https://bitbucket.org/verateam/vera/downloads/vera%2B%2B-1.3.0.tar.gz
RUN tar xvf vera++-1.3.0.tar.gz && \
 cd vera++-1.3.0 && \
 cmake . -DVERA_LUA=OFF -DVERA_PYTHON=OFF && \
 make install -j 4

COPY build.sh /




