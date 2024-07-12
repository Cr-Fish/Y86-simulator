#ifndef GUARD_Y86_h
#define GUARD_Y86_h
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#define ADR 3
#define HLT 2
#define AOK 1

struct CPU{
    std::vector<std::string> instr;
    int cod, B1fn;
    int ZF, SF, OF, Stat;
    int PC, PCnxt, PCcall;
    long long int REG[15];
    char MEM[10000];

    CPU();
    void prep();
    void read();
    void printReg();
    void printMem();
    void printCC();
    void halt();
    void nop();
    void rrmovq();
    void irmovq();
    void rmmovq();
    void mrmovq();
    void OPq();
    void jXX();
    void cmovXX();
    void call();
    void ret();
    void pushq();
    void popq();
    void iaddq();
};


#endif
