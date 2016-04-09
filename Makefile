
default: bin

bin: main.cpp
	g++ -std=c++11 main.cpp asm_parser.cpp
