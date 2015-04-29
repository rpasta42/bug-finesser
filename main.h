#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
//#include <regex>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <assert.h>

using namespace std;


#define error(x) assert(0);

typedef vector<string> vecStr;

vecStr split(const string &s, char delim);
void print_bin(uint64_t n);

typedef uint8_t Instr;
typedef uint8_t Reg;
typedef uint16_t Mem;
typedef uint32_t Const;

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

struct cmd {
   union {
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
      uint64_t uint64;
      uint8_t i;
   };
};

inline cmd inst(Instr i) {
   cmd ret;
   ret.i = i;
   return ret;
}
inline cmd inst(Instr i, Reg r) {
   cmd ret;
   ret.r = {i, r};
   return ret;
}
inline cmd inst(Instr i, Mem m) {
   cmd ret;
   ret.m = {i, m};
   return ret;
}
inline cmd inst(Instr i, Const c) {
   cmd ret;
   ret.c = {i, c};
   return ret;
}
inline cmd inst(Instr i, Reg r1, Reg r2) {
   cmd ret;
   ret.rr = {i, r1, r2};
   return ret;
}
inline cmd inst(Instr i, Reg r, Mem m) {
   cmd ret;
   ret.rm = {i, r, m};
   return ret;
}
inline cmd inst(Instr i, Mem m, Reg r) {
   cmd ret;
   ret.mr = {i, m, r};
   return ret;
}
inline cmd inst(Instr i, Reg r, Const c) {
   cmd ret;
   ret.rc = {i, r, c};
   return ret;
}
inline cmd inst(Instr i, Mem m, Const c) {
   cmd ret;
   ret.mc = {i, m, c};
   return ret;
}
#endif // MAIN_H_INCLUDED


/*
uint16_t    0-65535
uint8_t     0-255

memory   0-65,535
   io    50,000-65,535
   stack 30,000-49,999

nop
mov   reg/mem,       reg/mem/const
push  reg/mem/const
pop   reg/mem
lea   reg,           mem
   loads address of mem into reg
add   reg/mem,       reg/mem/const
sub   reg/mem,       reg/mem/const
inc   reg/mem
dec   reg/mem
cmp
*/

//command
//[0-7] [8-15][16-23] [24-31]
//inst      addr        reg
