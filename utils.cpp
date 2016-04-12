#include "main.h"

#include <termios.h>
#include <algorithm>
#include <fstream>
#include <streambuf>

OpType get_asm_op(string s) {
   if (s == "nop")
      return OpType::NOP;
   if (s == "halt")
      return OpType::HALT;
   if (s == "push")
      return OpType::PUSH;
   if (s == "pop")
      return OpType::POP;
   if (s == "inc")
      return OpType::INC;
   if (s == "dec")
      return OpType::DEC;
   if (s == "int")
      return OpType::INT;
   if (s == "call")
      return OpType::CALL;
   if (s == "jmp")
      return OpType::JMP;
   if (s == "je")
      return OpType::JE;
   if (s == "jne")
      return OpType::JNE;
   if (s == "jz")
      return OpType::JZ;
   if (s == "jnz")
      return OpType::JNZ;
   if (s == "jl")
      return OpType::JL;
   if (s == "jg")
      return OpType::JG;
   if (s == "mov")
      return OpType::MOV;
   if (s == "lea")
      return OpType::LEA;
   if (s == "cmp")
      return OpType::CMP;
   if (s == "mul")
      return OpType::MUL;
   if (s == "add")
      return OpType::ADD;
   if (s == "sub")
      return OpType::SUB;
   err("bad asm instruction");
}

char getch(bool echo) {
   char buf = 0;
   struct termios old = {0};
   if (tcgetattr(0, &old) < 0)
      perror("tcsetattr()");
   old.c_lflag &= ~ICANON;
   if (echo)
      old.c_lflag &= ~ECHO;
   old.c_cc[VMIN] = 1;
   old.c_cc[VTIME] = 0;
   if (tcsetattr(0, TCSANOW, &old) < 0)
      perror("tcsetattr ICANON");
   if (read(0, &buf, 1) < 0)
      perror ("read()");
   old.c_lflag |= ICANON;
   old.c_lflag |= ECHO;
   if (tcsetattr(0, TCSADRAIN, &old) < 0)
      perror ("tcsetattr ~ICANON");
   return (buf);
}

void print_bin(uint64_t n) {
   for (uint64_t i = 0; i < 63; i++) {
      cout << (bool)(n & ((uint64_t)1 << i));
   }
   cout << endl;
}

vecStr &split(const string &s, char delim, vecStr &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vecStr split(const string &s, char delim) {
    vecStr elems;
    split(s, delim, elems);
    return elems;
}

string read_file(string path) {
   ifstream f(path);
   string str;

   f.seekg(0, std::ios::end);
   str.reserve(f.tellg());
   f.seekg(0, std::ios::beg);

   str.assign((std::istreambuf_iterator<char>(f)),
               std::istreambuf_iterator<char>());
   return str;
}

