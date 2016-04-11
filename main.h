#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
//#include <regex>
#include <sstream>
#include <cstring>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>

using namespace std;

vector<uint64_t> kasm(string s);

#define error(x) assert(0);

typedef vector<string> vecStr;

vecStr split(const string &s, char delim);
inline void print_bin(uint64_t n) { cout << n; }


//TODO: mul
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

struct cmd { };
struct Op {
   union {
      uint64_t uint64;
      uint8_t i;
      struct {
         uint8_t i;
         uint8_t r;
      } r;
      struct {
         uint8_t i;
         uint16_t m;
      } m;
      struct {
         uint8_t i;
         uint32_t c;
      } c;
      struct {
         uint8_t i;
         uint8_t r1;
         uint8_t r2;
      } rr;
      struct {
         uint8_t i;
         uint8_t r;
         uint16_t a;
      } rm;
      struct {
         uint8_t i;
         uint16_t a;
         uint8_t r;
      } mr;
      struct {
         uint8_t i;
         uint8_t r;
         uint32_t c;
      } rc;
      struct {
         uint8_t i;
         uint16_t a;
         uint32_t c;
      } mc;
   };
};


#endif // MAIN_H_INCLUDED



