CFLAGS = `llvm-config --cflags`
CXXFLAGS = `llvm-config --cxxflags`
LDFLAGS = `llvm-config --ldflags`
LDLIBS = `llvm-config --libs --system-libs`

main : main.o wrap.s

wrap.s : wrap.ll
	llc wrap.ll

wrap.ll : codegen
	./codegen

codegen : codegen.o
	$(CXX) $(CXXFLAGS) -o codegen codegen.o $(LDFLAGS) $(LDLIBS)

codegen.o : codegen.c
	$(CC) $(CFLAGS) -c codegen.c

clean:
	rm -f *.o *.ll *.s
