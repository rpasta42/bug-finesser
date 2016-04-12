#include "main.h"
#include <map>

vector<u64> assemble(string s) {
   vector<u64> ret;
   s += '\n';

   vector<string> lines = split(s, '\n');
   map<string, int> label_addrs;
   u32 addr = 1; //temporarily load every application at 1. TODO: linker/loader

   for (auto line : lines) {
      vecStr words = split(line, ' ');
      if (words.size() == 2 && words[0] == "label")
         label_addrs[words[1].erase(0, 1)] = addr;
      addr++;
   }

   for (auto line : lines) {
      Instr instr;
      OpLayout layout;
      OpType type;

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
         char layout_s = words[1][0];
         string operand_s = words[1].erase(0, 1);
         u32 operand = (layout_s == '\'') ? 0 : stoi(operand_s);
         if (layout_s == '%')
            layout = OpLayout::R;
         else if (layout_s == '@')
            layout = OpLayout::M;
         else if (layout_s == '#')
            layout = OpLayout::C;
         else {
            assert(layout_s == '\'');
            if (op == "label") {
               if (label_addrs.find(operand_s) != label_addrs.end())
                  err("AsmErr: cannot re-use labels: " + operand_s);
               label_addrs[operand_s] = addr;
               continue;
            }
            if (label_addrs.find(operand_s) == label_addrs.end())
               err("Unknown label " + operand_s);
            layout = OpLayout::M;
            operand = label_addrs[operand_s];
         }

         switch (layout) {
         case OpLayout::R:
            instr.r = operand; //also have stol and stoll
            break;
         case OpLayout::C:
            instr.c = operand;
            break;
         case OpLayout::M:
            instr.a = operand;
            break;
         default:
            err("bad layout with 1 operand");
            break;
         }

         VecStr jmp_cmds = {"call", "jmp", "je", "jne", "jz", "jnz", "jl", "jg"};
         instr.o = Op(get_asm_op(op), layout).op;
         if (op != "push") {
            if (op == "int")
               assert(layout == OpLayout::C);
            else if (contains(jmp_cmds, string(op)))
               assert(layout == OpLayout::M);
            else
               assert(layout == OpLayout::R || layout == OpLayout::M);
         }
      }
      else if (numOp == 2) {
         char layout1 = words[1][0];
         char layout2 = words[2][0];
         u32 operand1 = stoi(words[1].erase(0, 1));
         u32 operand2 = stoi(words[2].erase(0, 1));

         if (layout1 == '%') {
            if (layout2 == '%')
               layout = OpLayout::RR;
            else if (layout2 == '@')
               layout = OpLayout::RM;
            else if (layout2 == '#')
               layout = OpLayout::RC;
            else err("bad layout register " + layout2);
         }
         else if (layout1 == '@') {
            if (layout2 == '%')
               layout = OpLayout::MR;
            else if (layout2 == '#')
               layout = OpLayout::MC;
            else err("bad layout memory " + layout2);
         }
         else err("bad layout (2 op): " + string(1, layout1) + " " + string(1, layout2));

         switch (layout) {
         case OpLayout::RR:
            instr.rr.r1 = operand1;
            instr.rr.r2 = operand2;
            break;
         case OpLayout::RM:
            instr.rm.r = operand1;
            instr.rm.a = operand2;
            break;
         case OpLayout::MR:
            instr.mr.a = operand1;
            instr.mr.r = operand2;
            break;
         case OpLayout::RC:
            instr.rc.r = operand1;
            instr.rc.c = operand2;
            break;
         case OpLayout::MC:
            instr.mc.a = operand1;
            instr.mc.c = operand2;
            break;
         default:
            err("bad layout");
            break;
         }

         instr.o = Op(get_asm_op(op), layout).op;
         //TODO: check layout
         if (op == "lea")
            assert(layout == OpLayout::RM);
      }
      else
         err(op + " got wrong number of arguments: " + to_string(numOp));
      addr++;
      ret.push_back(instr.uint64);
   }
   return ret;
}


