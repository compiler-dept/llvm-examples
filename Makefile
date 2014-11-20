CFLAGS=`llvm-config --cflags`

.PHONY: all clean

all: sample

sample: sample.o
	$(CXX) $< `llvm-config --cxxflags --ldflags --libs` -o $@

clean:
	rm -f sample *.o
