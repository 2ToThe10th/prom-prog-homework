FROM ubuntu:latest

WORKDIR /

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/time

RUN apt-get update && apt-get upgrade -y && DEBIAN_FRONTEND=noninteractive apt-get install -y git cmake libboost-all-dev curl build-essential libssl-dev libcurl4-openssl-dev gnutls-bin doxygen sendmail gtk-3.0 pkg-config libgtk-3-dev gsasl libghc-gsasl-dev libgnutls28-dev 

RUN git clone https://github.com/akhtyamovpavel/PatternsCollection.git PatternCollection

RUN mkdir /PatternCollection/cmake-build
WORKDIR /PatternCollection/cmake-build

RUN cmake ../

RUN make install

CMD bash