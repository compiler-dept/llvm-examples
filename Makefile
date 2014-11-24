CFLAGS=`llvm-config --cflags`
CXXFLAGS=`llvm-config --cxxflags`
LDFLAGS=`llvm-config --ldflags`
LDLIBS=`llvm-config --libs --system-libs`

OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all clean

all: main

main: main.o add.o
	$(CC) -o $@ $^

add.o: add.bc
	llc -filetype=obj $<

add.bc: sample
	./sample

sample: sample.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f main sample $(OBJECTS) add.o *.bc
