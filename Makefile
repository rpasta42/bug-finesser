
default: bin

bin: main.cpp
	g++ -std=c++14 -fpermissive utils.cpp main.cpp asm_parser.cpp
