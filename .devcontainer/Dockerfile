FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    sudo \
    git \
    build-essential cppcheck cmake \
    libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev \
    mesa-utils libgl1-mesa-glx


# create 'dev' user, add it to sudo group and set password
RUN mkdir /home/dev
RUN useradd -u 1000 dev && chown -R dev /home/dev
RUN adduser dev sudo
RUN echo "dev:dev"|chpasswd 