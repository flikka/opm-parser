FROM centos:latest
MAINTAINER Kristian Flikka <kristian@flikka.net>

ENV http_proxy=www-proxy.statoil.no:80 
ENV https_proxy=www-proxy.statoil.no:80
ENV HTTP_PROXY=www-proxy.statoil.no:80
ENV HTTPS_PROXY=www-proxy.statoil.no:80

RUN yum -y install openssh-server 
RUN yum -y install wget git cmake boost-devel cppcheck valgrind tcl-devel tk-devel
RUN yum -y groupinstall "Development Tools"
RUN wget https://bitbucket.org/verateam/vera/downloads/vera%2B%2B-1.3.0.tar.gz
RUN tar xvf vera++-1.3.0.tar.gz && \
 cd vera++-1.3.0 && \
 cmake . -DVERA_LUA=OFF -DVERA_PYTHON=OFF && \
 make install -j 4

RUN wget http://repo1.maven.org/maven2/org/codehaus/sonar/runner/sonar-runner-dist/2.4/sonar-runner-dist-2.4.zip && \
    unzip sonar-runner-dist-2.4.zip

#ssh
RUN mkdir /var/run/sshd

RUN adduser sonar
RUN echo 'sonar:sonar' | chpasswd

RUN /usr/sbin/sshd-keygen
RUN sed -ri 's/UsePAM yes/#UsePAM yes/g' /etc/ssh/sshd_config
RUN sed -ri 's/#UsePAM no/UsePAM no/g' /etc/ssh/sshd_config


EXPOSE 22
COPY build.sh /
CMD ["/usr/sbin/sshd", "-D"]




