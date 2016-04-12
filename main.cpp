#include "main.h"


struct Machine {
   u64 mem[65536];
   u64 r[256];
   u64 instr_ptr;
   u64 stack_ptr;
   Instr instr; //current instruction being executed

   Machine()
      : instr_ptr(0), stack_ptr(40000)
   {
      for (int i = 0; i < 255; i++)
         r[i] = 0;
      for (uint16_t i = 0; i < 65535; i++)
         mem[i] = 0;
   }

   //template <OpLayout L>
   void apply(Op op, std::function<void(void*, void*, u8)> f) {
      switch (op.getLayout()) {
      case OpLayout::NONE:
         f(NULL, NULL, 0);
         break;
      case OpLayout::R:
         f(&r[instr.r], NULL, 8);
         break;
      case OpLayout::M:
         f(&mem[instr.a], NULL, 8);
         break;
      case OpLayout::C:
         f((u64*)&instr.c, NULL, 4);
         break;
      case OpLayout::RR:
         f(&r[instr.rr.r1], &r[instr.rr.r2], 8);
         break;
      case OpLayout::RM:
         f(&r[instr.rm.r], &mem[instr.rm.a], 8);
         break;
      case OpLayout::MR:
         f(&r[instr.mr.a], &mem[instr.mr.r], 8);
         break;
      case OpLayout::RC:
         f(&r[instr.rc.r], &instr.rc.c, 4);
         break;
      case OpLayout::MC:
         f(&mem[instr.mc.a], &instr.mc.c, 4);
         break;
      default:
         err("Bad layout");
         break;
      }
   }

   void run() {
      while (true) {
         instr_ptr++;
         //cout << instr_ptr << endl;
         if (!mem[instr_ptr]) err("Bad instruction");

         instr.uint64 = mem[instr_ptr];
         Op op = Op(instr.o);

         OpLayout layout = op.getLayout();
         OpType type = op.getType();

         switch (type) {
         case OpType::NOP:
            continue;
            break;
         case OpType::HALT:
            return;
            break;
         case OpType::MOV: {
            apply(op, [&](void* a, void* b, u8 size) {
               memcpy(a, b, size);
               //*a = *b;
            });
            break;
         }
         case OpType::PUSH: {
            apply(op, [&](void* val, void* x, u8 size) {

            });
            break;
         }
         case OpType::INT: {
            assert(layout == OpLayout::C);
            u8 cmd = instr.c;
            switch (cmd) {
            case 0:
               usleep(r[0]);
               break;
            case 1:
               cout << (char)r[0];
               break;
            case 2:
               r[0] = getch(false);
               break;
            default:
               err("interrupt not implemented");
               cout << cmd;
               break;
            }
            break;
         }
         default:
            op.print();
            err("Command not implemented");
            break;
         }
      }
   }

};


vector<u64> assemble2(string s) {
   vector<u64> ret;

   auto lines = split(s, '\n');
   for (auto line : lines) {
      Instr instr;

      auto words = split(line, ' ');
      //for (auto word : words) {}
      if (words.size() == 0)
         continue;

      if (words.size() == 1) {
         if (words[0] == "nop") {
            instr.o = Op(OpType::NOP, OpLayout::NONE).op;
            ret.push_back(instr.uint64);
         }
      }
   }
   return ret;
}

int main() {
   string s = "mov $yo %blah";
   auto code = assemble(s);
}

int test_machine() {
   Machine m;

   Instr instr1;
   instr1.o = Op(OpType::MOV, OpLayout::MC).op;
   instr1.mc.a = 10;
   instr1.mc.c = 16;
   m.mem[1] = instr1.uint64;

   Instr instr2;
   instr2.o = Op(OpType::MOV, OpLayout::RC).op;
   instr2.rc.r = 1;
   instr2.rc.c = 16;
   m.mem[2] = instr2.uint64;

   Instr instr3;
   instr3.o = Op(OpType::INT, OpLayout::C).op;
   instr3.c = 2;
   m.mem[3] = instr3.uint64;

   Instr instr10;
   instr10.o = Op(OpType::HALT, OpLayout::NONE).op;
   m.mem[4] = instr10.uint64;

   m.run();

   //cout << m.r[0] << "\n";
   //cout << m.mem[5] << "\n";

   //char c = getch();
   cout << "registers: ";
   for (int i = 0; i < 20; i++)
      cout << m.r[i] << " ";

   cout << endl << "mem: ";
   for (int i = 0; i < 20; i++)
      cout << m.mem[i] << " ";
   cout << endl;
   //testOp();
}



/*
struct Machine {
   u64* mem; //mem[65536]
   u64 r[256];
   u64 instr_ptr;
   u64 stack_ptr;

   Machine(u64* mem_)
      : mem(mem_), instr_ptr(0), stack_ptr(30000)
   {
      for (int i = 0; i < 255; i++)
         r[i] = 0;
   }

   void run() {
      while (true) {
      //for (int i = 0; i < 1; i++) {
         Cmd c;
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
*/

int testOp() {
   Op x = Op(OpType::POP, OpLayout::NONE); x.print();
   Op(OpType::MOV, OpLayout::RR).print();
   Op(OpType::MOV, OpLayout::NONE).print();
}

/*Instr makeInstr(OpType t, OpLayout l, u64 a, u64 b) {
   Op o = Op(t, l);
   Instr s;
   s.o = o;
}*/


