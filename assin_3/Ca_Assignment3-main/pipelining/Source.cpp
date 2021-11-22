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
 
    
    startdecoder sd;
    sd.init_decode();
    sd.start_process();
    return 0;
}

