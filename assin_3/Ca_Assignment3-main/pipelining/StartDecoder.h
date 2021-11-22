#pragma once

#include "TypeDecoders.h"
#include <queue>
#include<string>
#include<fstream>
using namespace std;

constexpr auto INSMAX = 10;
extern const char* codeDesc[]; 
extern const char* signal[];
extern const uint16_t signal_mask[];

class startdecoder  { 
   
    decoder * dd;
    uint32_t inst;   //instruction fetched
    uint32_t curr_inst; // current inst under process
    uint16_t cnt;
    long imm12, imm20;  //immediate numeric value
    int desc, rs1, rs2, rd;   //register indx of current inst, if the inst do not refer the register, the value will be -1, ex: I, B types
    int rs1_val, rs2_val, rd_val;
    char t;       // opcode type R, B, I ....
    int pc;       // index for the next instruction from ins_array
    int Dep,  fet_sucess;      //dependencies flag, if Dep =0 no dependency on current inst registers
    int clk;
    uint32_t loop;
    uint32_t ins_array[INSMAX];    //machine code instructions
    int registers[32];       //alu registers

    bool bool_reg[32];    //to check the dependency
    
    //queues to represent pipeline
    //ins_array ---> fetch_Q ---> decode_Q  ---> exe_Q 
    typedef struct operand_val {
        int rs1, rs2, rd;
        int rs1_val, rs2_val, rd_val;
        int c_desc;
        int c_imm12_val, c_imm20_val;
       }op_val;

    queue <operand_val> fetch_Q;
    queue <operand_val> decode_Q;
    queue <operand_val> exe_Q;

    ofstream log;
    ofstream cycle;
    //simulation queue to log the events with message
    queue<string> simu;
    string msg;

    //helper functions
    void InsType();
    int increment_pc(uint16_t i);
    uint32_t get_reg_val(uint8_t rg);
    void set_reg_val(uint8_t rg, int val);
    int get_pc();
    void set_pc(uint32_t ins_addr);
    int check_depend(int rg);
    int check_depend(int r1, int r2, int r3);

public:
    startdecoder() {                         //main will call this constructor
        inst = curr_inst = imm12 = imm20 = clk = 0, pc=0;                  
        desc = cnt = 0;
        dd = new decoder();
        rs1 = rs2 = rd = -1;
        fet_sucess = loop= 1;
        Dep = 0;
        t = '\0';
        msg = "";
        for (int i = 0; i < 32; i++) {
            bool_reg[i] = false;
            registers[i] = 0;
        }
        log.open("log.txt");
        cycle.open("out.txt");
    }
    startdecoder(uint32_t ins) : inst(ins), cnt(0) {
      dd = new decoder(inst);
      imm12 = imm20 = 0;
       /* imm= desc= rs1= rs2= rd = 0;
        t = '\0';*/
        InsType();
    }
    
    int ALu_decode(op_val& op);   //decode the subfuctions
    int Fetch();  //get the ins from ins array , decode the registers, check for dependencies using buff array
    int execute(op_val& op); //execute the ins, call back for dependency resolving, initiate write back
    void write_back(op_val op);

    void init_decode();  //translate assembly file to machine code ins array
    void start_process();  //will call fetch, decode, execute and writeback funcs
    void end_process(int e);
    void printInstDescription();
    void printControlSignals();

   };