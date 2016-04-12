
default: bin

CXX=g++
#CXX=emcc
#EXTRA=-o target.html

bin: main.cpp
	$(CXX) -std=c++14 -fpermissive utils.cpp main.cpp asm_parser.cpp $(EXTRA)

clean:
	rm -f *.o a.out a.out.js target.html target.js
