CC=g++
LDLIBS=-lm -lcrypto
CXXFLAGS=-g --std=c++0x

OBJ=enc_sanitizer.o

build: rgt2108.2

rgt2108.2: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJ) -lcrypto

test: build

exec: build
	./rgt2108.2 $(ARGS)

.PHONY: clean
clean:
	rm -rf rgt2108.2 *.o *.core
