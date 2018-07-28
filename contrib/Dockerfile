FROM debian:stretch@sha256:f1f61086ea01a72b30c7287adee8c929e569853de03b7c462a8ac75e0d0224c4
RUN apt update -qq && apt upgrade --no-install-recommends -yqq && apt install automake build-essential ca-certificates gcc git imagemagick libgd-dev libncurses5-dev libxml2-dev make wget flex bison gperf python python-serial xxd autoconf libtool pkg-config lib32z1 unzip lib32z1 --no-install-recommends -yqq && apt -yqq autoremove && apt -yqq clean && rm -rf /var/lib/apt/lists/* /var/cache/* /tmp/*
RUN git clone --recursive --quiet --depth 1 --single-branch --branch v3.0.2 https://github.com/espressif/esp-idf.git /esp-idf
RUN git clone --recursive --quiet --depth 1 --single-branch https://github.com/PocketSprite/8bkc-sdk.git /8bkc-sdk && cd /8bkc-sdk && git checkout c3d4e1addb95d9b3370f415ac81e0ab5be4e8538
RUN wget -q https://dl.espressif.com/dl/xtensa-esp32-elf-linux64-1.22.0-80-g6c4433a-5.2.0.tar.gz && tar xzf *.tar.gz && rm *.tar.gz
ENV POCKETSPRITE_PATH=/8bkc-sdk
ENV IDF_PATH=/esp-idf
ENV PATH=/xtensa-esp32-elf/bin:${PATH}
CMD cd /8bkc-wally && make
