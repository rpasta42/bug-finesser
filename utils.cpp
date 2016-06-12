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

void print_hex_buff(uint8_t* buff, uint len, uint num_per_line) {
   cout << endl;
   uint word8 = 0;
   for (uint i = 0; i < len; i++) {
      //cout << std::hex << buffer[i] << " ";
      if (i % 8 == 0 && i != 0) {
         if (i != 0) printf("  ");
         word8++;
      }
      if (num_per_line != 0 && word8 == num_per_line) {
         printf("\n");
         word8 = 0;
      }
      printf("%02x ", buff[i]);
   }
   cout << endl;
}

vector<u64> read_machine_code(string path) {
   ifstream exe_file(path, ios::in | ios::binary);

   if (!exe_file)
      throw "can't open file for reading:" + path;

   exe_file.seekg(0, std::ios::end);
   int flen = exe_file.tellg();
   exe_file.seekg(0, std::ios::beg);

   uint8_t* buff = new uint8_t[flen];

   if (!exe_file.read((char*)buff, flen))
      throw "can't read from file" + path;

   vector<u64> code;
   for (int i = 0; i < flen / 8; i++)
      code.push_back(*(uint64_t*)(buff + i*8));

   free(buff);

   return code;
}

void write_machine_code(vector<u64> &asmb, string path) {
   uint buff_len = asmb.size() * 8;
   uint8_t* buffer = new uint8_t[buff_len];

   unsigned int i = 0;
   for (auto instr : asmb) {
      *(uint64_t*)(buffer + i*8) = instr;
      i++;
   }

   cout << "machine code: ";
   print_hex_buff(buffer, buff_len, 4);

   ofstream exe_file(path, ios::out | ios::binary);
   if (!exe_file)
      throw "can't open file for writing:" + path;

   if (!exe_file.write((char*)buffer, asmb.size()*8))
      throw "failed writing to " + path;

   free(buffer);
}

