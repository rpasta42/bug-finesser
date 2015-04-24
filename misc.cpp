#include "main.h"

void print_bin(uint64_t n) {
   for (uint64_t i = 0; i < 63; i++) {
      cout << (bool)(n & ((uint64_t)1 << i));
   }
   cout << endl;
}

vecStr &split(const string &s, char delim, vecStr &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vecStr split(const string &s, char delim) {
    vecStr elems;
    split(s, delim, elems);
    return elems;
}
