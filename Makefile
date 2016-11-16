CC=g++
LDLIBS=-lm -lcrypto
CXXFLAGS=-g --std=c++0x

OBJ=enc_sanitizer.o

build: rgt2108.2

rgt2108.2: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJ) -lcrypto

test: build
	./rgt2108.2 < ./tests/test1/test1.txt
	./rgt2108.2 < ./tests/test2/test2.txt


exec: build
	./rgt2108.2 $(ARGS)

.PHONY: clean
clean:
	rm -rf rgt2108.2 *.o *.core
