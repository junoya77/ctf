FROM debian:latest

#run sed -i 's@archive.ubuntu.com@kr.archive.ubuntu.com@g' /etc/apt/sources.list
# =========Install your package=========
RUN apt-get update && apt-get install -y \
make \
gcc  \
xinetd 
#checksec 
# ======================================

RUN mkdir -p /var/ctf
COPY flag /var/ctf/
RUN chmod 444 /var/ctf/flag

# ======Build and run your service======

COPY /src/casino_service /etc/xinetd.d/
RUN echo "casino_service 4000/tcp" >> /etc/services

RUN useradd -ms /bin/bash casinoapp
ADD /src /src
COPY /src/* /src/
RUN cd /src; make
WORKDIR /src
#RUN checksec -f casino

RUN service xinetd restart
ENTRYPOINT [ "xinetd", "-dontfork" ]
