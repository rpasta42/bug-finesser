
default: bin

bin: main.cpp
	g++ -std=c++14 main.cpp #asm_parser.cpp
