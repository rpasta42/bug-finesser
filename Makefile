
default: bin

bin: main.cpp
	g++ -std=c++14 utils.cpp main.cpp #asm_parser.cpp
