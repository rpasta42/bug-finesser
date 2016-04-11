#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
//#include <regex>
#include <sstream>
#include <cstring>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>

using namespace std;

vector<uint64_t> kasm(string s);

#define error(x) assert(0);

typedef vector<string> vecStr;

vecStr split(const string &s, char delim);
inline void print_bin(uint64_t n) { cout << n; }

enum class OperandType {
   Register, Memory, Constant
};

struct cmd { };


//TODO: mul
enum {
   //NOP, MOV, PUSH, POP, LEA, ADD, SUB, INC, DEC, CMP
   NOP, HALT,
   MOVrr, MOVrm, MOVmr, MOVrc, MOVmc,
   PUSHr, PUSHm, PUSHc,
   POPr, POPm,
   LEArm,
   ADDrr, ADDrm, ADDmr, ADDrc, ADDmc,
   SUBrr, SUBrm, SUBmr, SUBrc, SUBmc,
   INCr, INCm,
   DECr, DECm
};

struct Op {
   union {
      uint64_t uint64;
      uint8_t i;
      struct {
         uint8_t i;
         uint8_t r;
      } r;
      struct {
         uint8_t i;
         uint16_t m;
      } m;
      struct {
         uint8_t i;
         uint32_t c;
      } c;
      struct {
         uint8_t i;
         uint8_t r1;
         uint8_t r2;
      } rr;
      struct {
         uint8_t i;
         uint8_t r;
         uint16_t a;
      } rm;
      struct {
         uint8_t i;
         uint16_t a;
         uint8_t r;
      } mr;
      struct {
         uint8_t i;
         uint8_t r;
         uint32_t c;
      } rc;
      struct {
         uint8_t i;
         uint16_t a;
         uint32_t c;
      } mc;
   };
};

struct Operand {
   OperandType t;

   union {
      uint8_t regVal;
      uint16_t addrVal;
      uint32_t constVal;
   };

   template <class T>
   Operand(OperandType _t, T value)
      : t(_t)
   {
      if (t == OperandType::Register) {
         regVal = value;
      } else if (t == OperandType::Memory) {
         addrVal = value;
      } else if (t == OperandType::Constant) {
         constVal = value;
      }
   }
};
#define C_r
#define C_

class Opcode {
   Op o;

public:
   Opcode() {
      o.i = 0;
   }

   Opcode(uint64_t uint64) {
      o.uint64 = uint64;
   }

   Opcode(Instruction instr)
      : Opcode()
   {
      o.i = instr;
   }

   Opcode(Instruction instr, Operand a)
      : Opcode(instr)
   {
      if (a.t == OperandType.Register) {}
      else if (a.t == OperandType.Memory) {}
      else if (a.t == OperandType.Constant) {}
   }

   Opcode(Instruction instr, Operand a, Operand b)
      : Opcode(instr)
   {}


};

//uint64_t opcode(Instr i, )
struct Machine {
   uint64_t* mem; //mem[65536]
   uint64_t r[256];
   uint64_t instr_ptr;
   uint64_t stack_ptr;

   Machine(uint64_t* mem_)
      : mem(mem_), instr_ptr(0), stack_ptr(30000)
   {
      for (int i = 0; i < 255; i++)
         r[i] = 0;

      while (true) {
      //for (int i = 0; i < 1; i++) {
         cmd c;
         c.uint64 = mem[instr_ptr++];

         if (c.i == NOP)
            continue;
         else if (c.i == HALT)
            return;
         else if (c.i == MOVrr) {
            r[c.rr.r1] = r[c.rr.r2];
         }
         else if (c.i == MOVrm) {
            r[c.rm.r] = mem[c.rm.a];
         }
         else if (c.i == MOVmr) {}
         else if (c.i == MOVrc) {
            r[c.rc.r] = r[c.rc.c];
         }
         else if (c.i == MOVmc) {
            mem[c.mc.a] = c.mc.c;
         }
      }
   }

   void exec() {

   }

};


#endif // MAIN_H_INCLUDED



