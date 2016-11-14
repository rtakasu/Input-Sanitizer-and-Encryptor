CC=g++
LDLIBS=-lm -lcrypto
CXXFLAGS=-g --std=c++0x

OBJ=sanitizer.o

build: sanitizer

sanitizer: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJ) -lcrypto

.PHONY: clean
clean:
	rm -rf sanitizer *.o *.core
