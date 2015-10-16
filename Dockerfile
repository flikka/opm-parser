FROM centos:latest
MAINTAINER Kristian Flikka <kristian@flikka.net>
RUN yum -y install git
RUN git clone https://github.com/OPM/opm-parser.git