CFLAGS=`llvm-config --cflags`
CXXFLAGS=`llvm-config --cxxflags`
LDFLAGS=`llvm-config --ldflags`
LDLIBS=`llvm-config --libs --system-libs`

OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all sample clean

all: sample

sample: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f sample $(OBJECTS)
