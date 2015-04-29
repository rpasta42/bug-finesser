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
