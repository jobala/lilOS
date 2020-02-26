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
$ build-essential nasm xorriso grub-pc-bin bochs bochs-sdl
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
