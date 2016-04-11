#include "main.h"

//@address, %reg, #num, (TODO) $label
/*
push %1

*/

int main() {
   kasm("hello wlrd\ngdfgdf");
}

void exec() {
   uint64_t mem[65536];

   for (uint16_t i = 0; i < 65535; i++)
      mem[i] = 0;

   mem[0] = inst(MOVmc, (Mem)5, (Const)5).uint64;
   mem[1] = inst(HALT).uint64;

   print_bin(mem[5]);
   Machine m(mem);
   print_bin(mem[5]);

   //inst(4);

}


