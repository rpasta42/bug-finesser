#ifndef MAIN_H_INCLUDE
#define MAIN_H_INCLUDE

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <functional>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef vector<string> VecStr;

char getch(bool echo);
typedef vector<string> vecStr;
vecStr split(const string &s, char delim);
template <class T>
bool contains(vector<T> v, T item) {
   if (find(v.begin(), v.end(), item) != v.end())
      return true;
   return false;
}
string read_file(string path);

vector<u64> assemble(string s);

#define err(s) do { cout << "error: " << (s) << endl; exit(-1); } while (0)
#define debugp(s) cout << s;

#define STACK_START 40000
#define MACHINE_MEM 65536
#define NUM_REGISTERS 256

//address = u16
//register size u64, register specifier u8

//INT specifies operation based on constant passed to it
//INT 0 = sleep r1*microseconds
//INT 1 print r1 char
//INT 2 store character into r1
//INT 3 switch page r1 (TODO?)
//INT 4 halt (!!?? bad, already an instruction)

enum class OpType : u8 {
   NOP, HALT, //No args
   PUSH, POP, INC, DEC, INT, CALL, //1 arg
   JMP, JE, JNE, JZ, JNZ, JL, JG, //1 addr arg (jmp, eq, not eq, 0, not 0, <, >)
   MOV, LEA, CMP, MUL, ADD, SUB //2 args

   /*NOP, HALT,
   MOVrr, MOVrm, MOVmr, MOVrc, MOVmc,
   PUSHr, PUSHm, PUSHc,
   POPr, POPm,
   LEArm,
   ADDrr, ADDrm, ADDmr, ADDrc, ADDmc,
   SUBrr, SUBrm, SUBmr, SUBrc, SUBmc,
   INCr, INCm,
   DECr, DECm
   ==TODO
   CMP, GOTO, JE, JNE
*/
};

OpType get_asm_op(string s);

enum class OpLayout : u8 {
   NONE,
   R, M, C,
   RR, RM, MR, RC, MC
};

struct Op {
   u8 op;

   Op(u8 op_)
      : op(op_)
   {}
   Op(OpType opT, OpLayout opL)
      : op((u8)opT | ((u8)opL << 4))
   { }

   OpType getType() {
      return (OpType)((u8)(this->op << 4) >> 4); //op & (~(u8)0 << 4)
   }
   OpLayout getLayout() {
      return (OpLayout)(this->op >> 4);
   }
   void print() {
      cout << "OpType: ";
      switch (getType()) {
      case OpType::NOP:
         cout << "NOP";
         break;
      case OpType::MOV:
         cout << "MOV";
         break;
      case OpType::PUSH:
         cout << "PUSH";
         break;
      case OpType::POP:
         cout << "POP";
         break;
      case OpType::LEA:
         cout << "LEA";
         break;
      case OpType::ADD:
         cout << "ADD";
         break;
      case OpType::SUB:
         cout << "SUB";
         break;
      case OpType::INC:
         cout << "INC";
         break;
      case OpType::DEC:
         cout << "DEC";
         break;
      case OpType::CMP:
         cout << "CMP";
         break;
      default:
         cout << "unknown OpType";
         break;
      }
      cout << "\tOpLayout: ";
      switch (getLayout()) {
      case OpLayout::NONE:
         cout << "NONE";
         break;
      case OpLayout::R:
         cout << "Register";
         break;
      case OpLayout::M:
         cout << "Memory";
         break;
      case OpLayout::C:
         cout << "Constant";
         break;
      case OpLayout::RR:
         cout << "Register Register";
         break;
      case OpLayout::RM:
         cout << "Register Memory";
         break;
      case OpLayout::MR:
         cout << "Memory Register";
         break;
      case OpLayout::RC:
         cout << "Register Constant";
         break;
      case OpLayout::MC:
         cout << "Memory Constant";
         break;
      default:
         cout << "Unknown OpLayout";
         break;
      }
      cout << endl;
   }
};

#define pack_ __attribute__((packed))

struct Instr {
   union {
      u64 uint64;
      struct {
         u8 o : 8; //Opcode
         union {
            u8 r;
            u16 a;
            u32 c;
            struct {
               u8 r1;
               u8 r2;
            } pack_ rr;
            struct {
               u8 r;
               u16 a;
            } pack_ rm;
            struct {
               u16 a;
               u8 r;
            } pack_ mr;
            struct {
               u8 r;
               u32 c;
            } pack_ rc;
            struct {
               u16 a;
               u32 c;
            } pack_ mc;
         };
      } pack_;
   };
} pack_;

#endif //MAIN_H_INCLUDE

