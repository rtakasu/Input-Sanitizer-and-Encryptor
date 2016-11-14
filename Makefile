CC=g++
LDLIBS=-lm
CXXFLAGS=-g --std=c++0x

OBJ=sanitizer.o

build: sanitizer

sanitizer: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJ)

.PHONY: clean
clean:
	rm -rf sanitizer *.o *.core
