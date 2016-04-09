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

         int i;
         if (op == "push") {
            if (reg)
               i = PUSHr;
            else if (addr)
               i = PUSHm;
            else
               i = PUSHc;

         }
         else if (op == "pop") {
            if (reg)
               i = POPr;
            else if (addr)
               i = POPm;
            else assert(0);
         }
         else if (op == "inc") {
            if (reg)
               i = INCr;
            else if (addr)
               i = INCm;
            else assert(0);

         }
         else if (op == "dec") {
            if (reg)
               i = DECr;
            else if (addr)
               i = DECm;
            else assert(0);
         }
         else
            assert(string("unsupported instruction") == string("fail"));

         if (reg)
            ret.push_back(inst(i, (Reg)stoi(lex[1].erase(0, 1))).uint64);
         else if (addr)
            ret.push_back(inst(i, (Mem)stoi(lex[1].erase(0, 1))).uint64);
         else
            ret.push_back(inst(i, (Const)stoi(lex[1].erase(0, 1))).uint64);
      }
      else if (numOp == 2) {
         bool reg1  = (lex[1][0] == '%');
         bool addr1 = (lex[1][0] == '@');
         if (!reg1 && !addr1)
            assert(lex[1][0] == '#');

         bool reg2  = (lex[2][0] == '%');
         bool addr2 = (lex[2][0] == '@');
         if (!reg2 && !addr2)
            assert(lex[2][0] == '#');

         /*if (op == "MOV")
         LEA
         ADD
         SUB
         MUL*/

      }
      else {
         error(op + " cannot take " + string(numOp) + " arguments");
      }

   }
   return ret;
}
