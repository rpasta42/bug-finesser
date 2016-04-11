#ifndef MAIN_H_INCLUDE
#define MAIN_H_INCLUDE

#include <stdint.h>
#include <iostream>
#include <functional>

using namespace std;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

//address = u16
//register size u64, register specifier u8

//INT specifies operation based on constant passed to it
//INT 0 = sleep r1*microseconds
//INT 1 halt (!!?? bad, already an instruction)
//INT 2 print r1 char
//INT 3 store character into r1
//INT 4 switch page r1 (TODO?)

enum class OpType : u8 {
   NOP, MOV, PUSH, POP, LEA, ADD, SUB, INC, DEC, CMP, HALT, GOTO, INT
   /*NOP, HALT,
   MOVrr, MOVrm, MOVmr, MOVrc, MOVmc,
   PUSHr, PUSHm, PUSHc,
   POPr, POPm,
   LEArm,
   ADDrr, ADDrm, ADDmr, ADDrc, ADDmc,
   SUBrr, SUBrm, SUBmr, SUBrc, SUBmc,
   INCr, INCm,
   DECr, DECm*/
};

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

struct Instr {
   union {
      u64 uint64;
      struct {
         u8 o : 8; //Opcode
         union {
            u8 r : 8;
            u16 a : 16;
            u32 c : 32;
            struct {
               u8 r1 : 8;
               u8 r2 : 8;
            } rr;
            struct {
               u8 r : 8;
               u16 a : 8;
            } rm;
            struct {
               u16 a : 16;
               u8 r : 8;
            } mr;
            struct {
               u8 r : 8;
               u32 c : 32;
            } rc;
            struct {
               u16 a : 16;
               u32 c : 32;
            } mc;
         };
      };
   };
} __attribute__((packed));

#endif //MAIN_H_INCLUDE

