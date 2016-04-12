
default: bin

CXX=g++
#CXX=emcc
#EXTRA=-g -o target.html
EXTRA=-g
#-fpermissive

bin: main.cpp
	$(CXX) -std=c++14 utils.cpp main.cpp asm_parser.cpp $(EXTRA)

clean:
	rm -f *.o a.out a.out.js target.html target.js
