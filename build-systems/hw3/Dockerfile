FROM ubuntu:latest

WORKDIR /
RUN apt-get update && apt-get upgrade -y && DEBIAN_FRONTEND=noninteractive apt-get install -y git wget tar xz-utils cmake make qemu-user

RUN git clone https://github.com/akhtyamovpavel/TechProgSimpleLibrary.git TechProgSimpleLibrary

RUN mkdir /TechProgSimpleLibrary/cmake-build

WORKDIR /TechProgSimpleLibrary/cmake-build

RUN wget https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz -O gcc-linaro.tar.xz

RUN wget http://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/armv8l-linux-gnueabihf/sysroot-glibc-linaro-2.25-2019.12-armv8l-linux-gnueabihf.tar.xz -O sysroot-glibc-linaro.tar.xz

RUN tar -xJf gcc-linaro.tar.xz
RUN mv gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf gcc-linaro

RUN tar -xJf sysroot-glibc-linaro.tar.xz
RUN mv sysroot-glibc-linaro-2.25-2019.12-armv8l-linux-gnueabihf sysroot-glibc-linaro

COPY CMakeLists.txt /TechProgSimpleLibrary/CMakeLists.txt

RUN CC=gcc-linaro/bin/arm-linux-gnueabihf-gcc CXX=gcc-linaro/bin/arm-linux-gnueabihf-g++ cmake -DCMAKE_INSTALL_PREFIX=/ready_program/ ..

RUN make install

RUN echo "From original place"
RUN qemu-arm -L sysroot-glibc-linaro /ready_program/bin/Main
RUN qemu-arm -L sysroot-glibc-linaro /ready_program/bin/MainLib

RUN cp -r /ready_program/ /copy_of_ready_program/

RUN echo "From copy place"
RUN qemu-arm -L sysroot-glibc-linaro /copy_of_ready_program/bin/Main
RUN qemu-arm -L sysroot-glibc-linaro /copy_of_ready_program/bin/MainLib

CMD bash
