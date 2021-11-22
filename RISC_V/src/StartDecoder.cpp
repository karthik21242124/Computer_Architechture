#include "StartDecoder.h"
#include <bitset>
extern const char* codeDesc[] = {
  "add", "addi", "sub", "mul", "lw", "sw", "sb", "lh", "lb", "sh", "lui", "or", "nor", "xor", 
  "andi","ori", "xori", "sll", "sra", "srl", "sltu", "slt", "sltiu", "slti", "slli", "srai", "srli",
  "movn", "bgeu", "beq", "bne", "bge", "bltu", "blt", "j", "jalr", "jal", "and", "lbu", "lhu","mul",
  "mulh","mulhsu","mulhu","div","divu","rem","remu","auipc"};

extern const char* signal[] = { "reg_wen","reg_ren","alu_op","mem_wen",	"mem_ren","sel1", "sel2","sel3",
"sel4","sel5","sel6","sel7","sel8","branch","auipc","lui"};
  void startdecoder::InsType()
  {
     
   t = dd->getOPcode();
    switch (t)
    {
    case 'R':   dd = new R_decode(inst);
                desc= dd->getFuncDesc();
                rs1 = dd->getRs1();
                rs2 = dd->getRs2();
                rd = dd->getRd();
                cnt = dd->getControlSignals(desc);
                break;
    case 'I':   dd = new I_decode(inst);
                desc = dd->getFuncDesc();
                rs1 = dd->getRs1();
                rs2 = dd->getRs2();  
                rd = dd->getRd();
                imm12 = dd->getImm12();
                cnt = dd->getControlSignals(desc); 
                break;
    case 'S':   dd = new S_decode(inst);
                desc = dd->getFuncDesc();
                rs1 = dd->getRs1();
                rs2 = dd->getRs2();  
                imm12 = dd->getImm12();
                cnt = dd->getControlSignals(desc);
                break;
    case 'B':   dd = new B_decode(inst);
                 desc = dd->getFuncDesc();
                 rs1 = dd->getRs1();
                 rs2 = dd->getRs2();
                 imm12 = dd->getImm12b();
                 
                 cnt = dd->getControlSignals(desc);
                 break;
    case 'L':   dd = new L_decode(inst);
                 desc = dd->getFuncDesc();
                rs1 = dd->getRs1();
                rs2 = dd->getRd();
   
                cnt = dd->getControlSignals(desc);
                 break;
    case 'J':   dd = new J_decode(inst);
                desc = dd->getFuncDesc();
                rs1 = dd->getRs1();
                rs2 = dd->getRs2();  //Rs2 is the shiftamount bits
                rd = dd->getRd();
                imm12 = dd->getImm12();
                cnt = dd->getControlSignals(desc); 
                break;
    case 'A':   dd = new J_decode(inst);
                desc = dd->getFuncDesc();
                rs1 = dd->getRs1();
                rs2 = dd->getRs2();  
                rd = dd->getRd();
                imm20 = dd->getImm20();
                cnt = dd->getControlSignals(desc);
                break;
    case 'U':   dd = new U_decode(inst);
                desc = dd->getFuncDesc();
                rd = dd->getRd();
                imm20 = dd->getImm20();
                cnt = dd->getControlSignals(desc); 
                break;
    case 'W':   dd = new U_decode(inst);
                desc = dd->getFuncDesc();
                 rd = dd->getRd();
                imm20 = dd->getImm20();
                 cnt = dd->getControlSignals(desc); 
                break;

    }
}
  void startdecoder::printInstDescription() {
      if (t == 'W')
      {
          cout << "Opcode Type: " << "U" << endl;
      }
      else if (t == 'A')
      {
          cout << "Opcode Type: " << "J" << endl;
      }
      else
      cout << "Opcode Type: " << t << endl;
      switch (t)
      {
      case 'R':     
                    cout << "Inst: " << codeDesc[desc] << " " << "x" << rd << " " << "x" << rs1 << " " << "x" << rs2 << endl;
       
          break;
      case 'I':    if(desc==24 || desc == 25 || desc == 26)
                   cout << "Inst: " << codeDesc[desc] << " " << "x" << rd << " " << "x" << rs1 << " " <<  rs2 << endl;
                   else
                    cout << "Inst: " << codeDesc[desc] << " " << "x" << rd << " " << "x" << rs1 << " " << imm12 << endl;
          break;
      case 'S':     cout << "Inst: " << codeDesc[desc] << " " << "x" << rs2 << " " << imm12 << "(" <<"x" << rs1 << ")" << endl;
          break;
      case 'B':     cout << "Inst: " << codeDesc[desc] << " " << "x" <<rs1 << " "<<"x" << rs2 << " " << imm12 << endl;
          break;
      case 'L':    cout << "Inst: " << codeDesc[desc] << " " << "x" << rs2 << " " << imm12 << "(" << "x" << rs1 << ")" << endl;
          break;
      case 'J':    cout << "Inst: " << codeDesc[desc] << " " << "x" << rd << " " << imm12 << "(" << "x" << rs1 << ")" << endl;
          break;
      case 'U':    cout << "Inst: " << codeDesc[desc] << " " << "x" << rd << " " << imm20 << endl;
          break;
      case 'W':    cout << "Inst: " << codeDesc[desc] << " " << "x" << rd << " " << imm20 << endl;
          break;
      case 'A':    cout << "Inst: " << codeDesc[desc] << " " << "x" << rd << " " << imm20  << endl;
          break;
      default:
          break;
      }
  
  }
  void startdecoder::printControlSignals()
  {
      cout <<"Control Signals: " << endl;
     /* cout << "reg_wen,   reg_ren jump,    branch,  alu_op,  mem_wen, mem_ren, sel1,    sel2,	sel3,	sel4,	sel5" << endl;
      cout << "Signals: " << bitset<16>(cnt)<<endl<<endl;*/
      bitset<16> controlBits(cnt);
      for (int i = 15; i >=0; --i) {
          if (i % 4 == 0) cout << endl;
          if (controlBits.test(i))     //test method will be true if ith bit is set.
              cout << signal[15-i] << ": " << 1<<" ";
          else
              cout << signal[15-i] << ": " << 0<<" ";
       }
      cout << endl;
      cout << "------------------------------"<<endl;
  }
