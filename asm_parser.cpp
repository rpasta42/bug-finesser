#include "asm_parser.h"

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
      }
      else {
         error(op + " cannot take " + string(numOp) + " arguments");
      }

   }
   return ret;
}
