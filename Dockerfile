FROM ubuntu

RUN apt-get update 
RUN apt-get install -y build-essential
RUN apt-get install -y nasm 
RUN apt-get install -y xorriso 
RUN apt-get install -y grub-pc-bin

COPY . /var/www
WORKDIR /var/www

CMD ["make", "os.iso"]

