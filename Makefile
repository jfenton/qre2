CC := g++

CFLAGS := -std=c++11 -pthread -I./re2 -O3 -DNDEBUG -DKXVER=3 -Wall -Wextra
CFLAGS_32 := -m32
CFLAGS_64 := -m64

CFLAGS_M := -bundle -undefined dynamic_lookup
CFLAGS_L := -shared -fPIC -lstdc++

SRC = qre2.cpp

RE2_CFLAGS = -O3 -fPIC
RE2_LIB = re2/obj/libre2.a
RE2_LIB32 = libre2_32.a
RE2_LIB64 = libre2_64.a

$(RE2_LIB32):
	cd re2 && make clean && make CXXFLAGS="-m32 $(RE2_CFLAGS)" LDFLAGS="-m32"
	mv $(RE2_LIB) $(RE2_LIB32)

$(RE2_LIB64):
	cd re2 && make clean && make CXXFLAGS="-m64 $(RE2_CFLAGS)" LDFLAGS="-m64"
	mv $(RE2_LIB) $(RE2_LIB64)

m64: $(SRC) $(RE2_LIB64)
	$(CC) $(CFLAGS) $(CFLAGS_64) $(CFLAGS_M) $(SRC) $(RE2_LIB64) -o qre2_m64.so

m32: $(SRC) $(RE2_LIB32)
	$(CC) $(CFLAGS) $(CFLAGS_32) $(CFLAGS_M) $(SRC) $(RE2_LIB32) -o qre2_m32.so

l64: $(SRC) $(RE2_LIB64)
	$(CC) $(CFLAGS) $(CFLAGS_64) $(CFLAGS_L) $(SRC) $(RE2_LIB64) -o qre2_l64.so

l32: $(SRC) $(RE2_LIB32)
	$(CC) $(CFLAGS) $(CFLAGS_32) $(CFLAGS_L) $(SRC) $(RE2_LIB32) -o qre2_l32.so

clean:
	rm -f *.so *.a

install:
	if [ -z "${QHOME}" ] ; then echo "QHOME not defined!" ; exit 1 ; fi
	[ -f "qre2_m64.so" ] && cp qre2_m64.so ${QHOME}/m64/qre2.so || true
	[ -f "qre2_m32.so" ] && cp qre2_m32.so ${QHOME}/m32/qre2.so || true
	[ -f "qre2_l64.so" ] && cp qre2_l64.so ${QHOME}/l64/qre2.so || true
	[ -f "qre2_l32.so" ] && cp qre2_l32.so ${QHOME}/l32/qre2.so || true

.PHONY: clean install m32 m64 l32 l64
