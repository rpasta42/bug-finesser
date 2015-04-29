#include "main.h"
#include "asm_parser.h"

enum {
   //NOP, MOV, PUSH, POP, LEA, ADD, SUB, INC, DEC, CMP
   NOP, HALT,
   MOVrr, MOVrm, MOVmr, MOVrc, MOVmc,
   PUSHr, PUSHm, PUSHc,
   POPr, POPm,
   LEArm,
   ADDrr, ADDrm, ADDmr, ADDrc, ADDmc,
   SUBrr, SUBrm, SUBmr, SUBrc, SUBmc,
   INCr, INCm,
   DECr, DECm
};

struct Machine {
   uint64_t* mem; //mem[65536]
   uint64_t r[256];
   uint64_t instr_ptr;
   uint64_t stack_ptr;

   Machine(uint64_t* mem_)
      : mem(mem_), instr_ptr(0), stack_ptr(30000)
   {
      for (int i = 0; i < 255; i++)
         r[i] = 0;

      while (true) {
      //for (int i = 0; i < 1; i++) {
         cmd c;
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
//@address, %reg, #num, (TODO) $label
//push %1



int main() {
   kasm("hello wlrd\ngdfgdf");
}


int main1() {


   uint64_t mem[65536];

   for (uint16_t i = 0; i < 65535; i++)
      mem[i] = 0;

   mem[0] = inst(MOVmc, (Mem)5, (Const)5).uint64;
   mem[1] = inst(HALT).uint64;

   print_bin(mem[5]);
   Machine m(mem);
   print_bin(mem[5]);

   //inst(4);

   return 0;
}
