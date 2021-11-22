#pragma once
#include "decoder.h"

class I_decode : public decoder {
public:
    I_decode() :decoder() {}
    I_decode(uint32_t ins) :decoder(ins) {}

     int getFuncDesc();
     uint16_t getControlSignals(int desc);
    
     uint16_t getImm12();
};

class R_decode : public decoder {
public:
    R_decode() :decoder() {}
    R_decode(uint32_t ins) :decoder(ins) {}
  
    virtual int getFuncDesc();
    virtual uint16_t getControlSignals(int desc);
};

class S_decode : public decoder {
public:
    S_decode() :decoder() {}
    S_decode(uint32_t ins) :decoder(ins) {}

    virtual int getFuncDesc();
    virtual uint16_t getControlSignals(int desc);
    virtual uint16_t getImm12();
};

class L_decode : public decoder {
public:
    L_decode() :decoder() {}
    L_decode(uint32_t ins) :decoder(ins) {}

    virtual int getFuncDesc();
    virtual uint16_t getControlSignals(int desc);
    virtual uint16_t getImm12();
};

class B_decode : public decoder {
public:
    B_decode() :decoder() {}
    B_decode(uint32_t ins) :decoder(ins) {}

    virtual uint32_t getImm12b();
    virtual int getFuncDesc();
    virtual uint16_t getControlSignals(int desc);
  //  virtual uint16_t getImm12();
};
class J_decode : public decoder {
public:
    J_decode() :decoder() {}
    J_decode(uint32_t ins) :decoder(ins) {}
    virtual uint16_t getImm12();
    virtual uint32_t getImm20();
    int getFuncDesc();
    uint16_t getControlSignals(int desc);
   
};

class U_decode : public decoder {
public:
    U_decode() :decoder() {}
    U_decode(uint32_t ins) :decoder(ins) {}

    int getFuncDesc();
    uint16_t getControlSignals(int desc);

   virtual uint32_t getImm20();
};
/*class A_decode : public decoder {
public:
    A_decode() :decoder() {}
    A_decode(uint32_t ins) :decoder(ins) {}

    int getFuncDesc();
    uint16_t getControlSignals(int desc);

     //uint16_t getImm12();
     virtual uint32_t getImm20();

};*/
