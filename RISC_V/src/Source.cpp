// RISC-v.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "StartDecoder.h"
#include <bitset>
#include <string>
using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        cout << "instruction file name missing" << endl;
        cout << "Usage:     Source.exe filename" << std::endl;
        return -1;
    }
   ifstream insFile(argv[1], ios::in);
    if(!insFile) {
      cout << "Cannot open file!" << endl;
      return -1;
   }
    string ins_buf;
    uint32_t ins_bin;
   
    while (getline( insFile, ins_buf)) {
      if (ins_buf.size() == NULL) break;
        ins_bin = 0b0000000000000000000000000000000;
        if(ins_buf.size() != 32)
        {
            cout << "invalid instruction code.\ninstruction must have 32 bits" << endl;
            return -1;
        }
        for (int i = 31; i >=0; --i) {

            if (ins_buf[i] == '1') {
                ins_bin = ins_bin | 1 << (31 - i);
            }
         }

       /* for (int i = 0; i < 32; i++) {
            if (ins_buf[i] == '1') 
                ins_bin = ins_bin | (1<< i)  //   01000000000000000000

        }*/
        startdecoder sd(ins_bin);
        sd.printInstDescription();
        sd.printControlSignals(); 

    }
     return 0;
}

