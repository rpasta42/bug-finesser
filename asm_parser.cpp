#include "main.h"
vector<u64> assemble(string s) {
   vector<u64> ret;

   s += '\n';

   vector<string> lines = split(s, '\n');
   for (auto line : lines) {
      Instr instr;

      //cout << lines[i] << endl;
      vecStr words = split(line, ' ');
      if (words.size() == 0 || words[0] == ";")
         continue;
      int numOp = words.size() - 1;

      string op = words[0];

      if (numOp == 0) {
         //assert(op == "nop" || op == "halt");
         if (op == "nop")
            instr.o = Op(OpType::NOP, OpLayout::NONE).op;
         else if (op == "halt")
            instr.o = Op(OpType::HALT, OpLayout::NONE).op;
         else
            err(op + " needs more than 0 arguments");
      }
      else if (numOp == 1) {//push, pop, inc, dec
         bool reg  = (words[1][0] == '%');
         bool addr = (words[1][0] == '@');
         if (!reg && !addr)
            assert(words[1][0] == '#');
         OpLayout layout = reg ? OpLayout::R :
                                 (addr ? OpLayout::M : OpLayout::C);
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
         err(op + " cannot take " + string(numOp) + " arguments");
      }
      ret.push_back(instr.uint64);
   }
   return ret;
}


