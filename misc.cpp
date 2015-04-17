#include "main.h"

void print_bin(uint64_t n) {
   for (uint64_t i = 0; i < 63; i++) {
      cout << (bool)(n & ((uint64_t)1 << i));
   }
   cout << endl;
}
