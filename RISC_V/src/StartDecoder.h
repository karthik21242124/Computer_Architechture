#pragma once

#include "TypeDecoders.h"

 
extern const char* codeDesc[]; 
extern const char* signal[];
class startdecoder  { 
   
    decoder * dd;
    uint32_t inst;
    uint16_t cnt;
    uint32_t imm12, imm20;
    int desc, rs1, rs2, rd;
    char t;
    void InsType();
public:
    startdecoder() : cnt(0), dd(NULL) {
        inst =imm12 =imm20 = desc = rs1 = rs2 = rd = 0;
        t = '\0';
    }
    startdecoder(uint32_t ins) : inst(ins), cnt(0) {
      dd = new decoder(inst);
      imm12 = imm20 = 0;
       /* imm= desc= rs1= rs2= rd = 0;
        t = '\0';*/
        InsType();
    }
   
    void printInstDescription();
    void printControlSignals();

   };