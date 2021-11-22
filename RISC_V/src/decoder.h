#pragma once
#include <iostream>
using namespace std;

class decoder {
public:
    uint32_t inst;
    decoder(): inst(0) {}
    decoder(uint32_t ins) : inst(ins) {}

    char getOPcode();
    uint8_t  getFun3();

    uint8_t getFun7(); 

    uint8_t getRd();
    uint8_t getRs1();
    uint8_t getRs2();
   
  virtual  uint16_t getControlSignals(int desc);
   virtual  int getFuncDesc();
   virtual uint16_t getImm12();
   virtual uint32_t getImm12b();
   virtual uint32_t getImm20();

 

};
