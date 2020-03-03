# Setting Up Your Environment

In this article I go over setting up your environment in different host machines.

## Linux

Linux has the easiest set up. All you need to do is install the following dependencies

```
$ build-essential nasm xorriso grub-pc-bin bochs bochs-sdl
```

## Windows

For windows we need a linux environment. You can achieve this using the Windows Subsystem for Linux. I have tested with Ubuntu and it is what I recommend for this tutorial. After getting Ubuntu installed, install the following software.

```
$ build-essential nasm xorriso grub-pc-bin bochs bochs-sdl qemu-user-static bochs-x
$ update-binfmts --install i386 /usr/bin/qemu-i386-static --magic '\x7fELF\x01\x01\x01\x03\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x03\x00\x01\x00\x00\x00' --mask '\xff\xff\xff\xff\xff\xff\xff\xfc\xff\xff\xff\xff\xff\xff\xff\xff\xf8\xff\xff\xff\xff\xff\xff\xff'

```
Then run the command below

```
sudo service binfmt-support start
```

## MacOS

For MacOS I recommend using Docker. It came as a surprise to me that MacOS is actually not Linux enough to use. Install Docker then create a Dockerfile and write the following:

```docker
FROM ubuntu

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y nasm
RUN apt-get install -y xorriso
RUN apt-get install -y grub-pc-bin

COPY . /var/www
WORKDIR /var/www

CMD ["make", "os.iso"]
```

Next, we  write some code😊
