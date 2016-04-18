
default: bin

CXX=g++
#CXX=emcc
#EXTRA=-g -o target.html
EXTRA=-g
#-fpermissive

bin: main.cpp
	$(CXX) -std=c++14 utils.cpp main.cpp asm_parser.cpp $(EXTRA)

clean:
	rm -f llvm/*.bc llvm/*.s llvm/a.out llvm/*.o *.o a.out a.out.js a.out.js.map target.html target.js
