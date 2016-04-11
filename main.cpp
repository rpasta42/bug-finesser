#include "main.h"

template <class A, class B>
void opMov(A *a, B *b) {
   a = b;
}

#define err(s) do { cout << "error" << s; exit(-1); } while (0)
#define debugp(s) cout << s;

struct Machine {
   u64 mem[65536];
   u64 r[256];
   u64 instr_ptr;
   u64 stack_ptr;
   Instr instr; //current instruction being executed

   Machine()
      : instr_ptr(0), stack_ptr(30000)
   {
      for (int i = 0; i < 255; i++)
         r[i] = 0;
      for (uint16_t i = 0; i < 65535; i++)
         mem[i] = 0;
   }

   //template <OpLayout L>
   void apply(Op op, std::function<void(u64*, u64*)> f) {
      switch (op.getLayout()) {
      case OpLayout::NONE:
         f(NULL, NULL);
         break;
      case OpLayout::R:
         f(&r[instr.r], NULL);
         break;
      case OpLayout::M:
         f(&mem[instr.a], NULL);
         break;
      case OpLayout::C:
         f((u64*)&instr.c, NULL);
         break;
      case OpLayout::RR:
         f(&r[instr.rr.r1], &r[instr.rr.r2]);
         break;
      case OpLayout::RM:
         f(&r[instr.rm.r], &mem[instr.rm.a]);
         break;
      case OpLayout::MR:
         f(&r[instr.mr.a], &mem[instr.mr.r]);
         break;
      case OpLayout::RC:
         f(&r[instr.rc.r], (u64*)&instr.rc.c);
         break;
      case OpLayout::MC:
         f(&mem[instr.mc.a], (u64*)&instr.mc.c);
         break;
      default:
         err("Bad layout");
         break;
      }
   }

   void run() {
      while (true) {
         instr_ptr++;
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
            apply(op, [&](auto a, auto b) {
               *a = *b;
            });
            break;
         }
            /*switch (layout) {
            case OpLayout::RR: r[instr.rr.r1] = r[instr.rr.r2]; break;
            case OpLayout::RM: r[instr.rm.r] = r[instr.rc.c]; break;
            case OpLayout::MR: break;
            }*/
         default:
            err("Command not implemented");
         }
      }
   }

};

int main() {
   Machine m;

   Instr instr1;
   instr1.o = Op(OpType::MOV, OpLayout::MC).op;
   instr1.mc.a = 5;
   instr1.mc.c = 16;
   m.mem[1] = instr1.uint64;

   Instr instr2;
   instr2.o = Op(OpType::MOV, OpLayout::RC).op;
   instr2.rc.r = 0;
   instr2.rc.c = 16;
   m.mem[2] = instr2.uint64;

   Instr instr10;
   instr10.o = Op(OpType::HALT, OpLayout::NONE).op;
   m.mem[3] = instr10.uint64;

   m.run();

   //cout << m.r[0] << "\n";
   cout << m.mem[5] << "\n";

   /*cout << "registers: ";
   for (int i = 0; i < 20; i++)
      cout << m.r[i] << " ";

   cout << endl << "mem: ";
   for (int i = 0; i < 20; i++)
      cout << m.mem[i] << " ";
   cout << endl;*/
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



