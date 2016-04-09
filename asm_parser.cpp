#include "asm_parser.h"

/*
typedef uint8_t Instr;
typedef uint8_t Reg;
typedef uint16_t Mem;
typedef uint32_t Const;
*/

void error(string s) {
   cout << s;
}

enum class OperandType {
   Register, Memory, Constant
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

enum Instruction : uint8_t {
   NOP, MOV, PUSH, POP, LEA, ADD, SUB, INC, DEC, CMP
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

vector<uint64_t> kasm(string s) {
   vector<uint64_t> ret;
   s += '\n';

   vector<string> lines;
   string line = "";
   for (int i = 0; i < s.length(); i++) {
      if (s[i] != '\n')
         line += s[i];
      else {
         lines.push_back(line);
         line = "";
      }
   }

   for (int i = 0; i < lines.size(); i++) {
      //cout << lines[i] << endl;
      vecStr lex = split(lines[i], ' ');
      int numOp = lex.size() - 1;

      string op = lex[0];

      if (numOp == 0) {
         //assert(op == "nop" || op == "halt");
         if (op == "nop")
            ret.push_back(inst(NOP).uint64);
         else if (op == "halt")
            ret.push_back(inst(HALT).uint64);
         else
            error(op + " needs more than 0 arguments");
      }
      else if (numOp == 1) {//push, pop, inc, dec
         bool reg  = (lex[1][0] == '%');
         bool addr = (lex[1][0] == '@');
         if (!reg && !addr)
            assert(lex[1][0] == '#');

         if (op == "push") {
            if (reg)
               ret.push_back(inst(PUSHr, stoi(lex[1].erase(0, 1))));
            else if (addr) {

            }
         }


         if (reg) {
         //if (op == "push")
         }
         if ()

      }
      else if (numOp == 2) {}
      else {
         error(op + " cannot take " + string(numOp) + " arguments");
      }

   }
   return ret;
}
