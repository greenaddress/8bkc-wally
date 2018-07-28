COMPONENT_OWNBUILDTARGET := true
COMPONENT_OWNCLEANTARGET := true

build:
	cd $(COMPONENT_PATH) && \
        export CFLAGS="-fno-stack-protector ${CFLAGS}" && ./tools/autogen.sh && \
        ./configure --enable-tests=no --enable-static=no --enable-shared=no --with-asm=no --enable-lto=no --disable-swig-java --disable-js-wrappers --disable-swig-python --disable-dependency-tracking --host=xtensa-esp32-elf && \
        $(MAKE) -o configure && \
        $(AR) cru $(COMPONENT_BUILD_DIR)/$(COMPONENT_LIBRARY) src/secp256k1/src/libsecp256k1_la-secp256k1.o src/*.o src/ccan/ccan/crypto/sha256/libwallycore_la-sha256.o src/ccan/ccan/crypto/sha512/libwallycore_la-sha512.o src/ccan/ccan/crypto/ripemd160/libwallycore_la-ripemd160.o

clean:
	rm -fr $(COMPONENT_BUILD_DIR)/*.a ; \
        cd $(COMPONENT_PATH) ; \
        ./tools/cleanup.sh

