#include "StartDecoder.h" 
#include <bitset>
#include <set>

extern const char* codeDesc[] = {
  "add", "addi", "sub", "mul", "lw", "sw", "sb", "lh", "lb", "sh", "lui", "or", "nor", "xor", 
  "andi","ori", "xori", "sll", "sra", "srl", "sltu", "slt", "sltiu", "slti", "slli", "srai", "srli",
  "movn", "bgeu", "beq", "bne", "bge", "bltu", "blt", "j", "jalr", "jal", "and", "lbu", "lhu","mul",
  "mulh","mulhsu","mulhu","div","divu","rem","remu","auipc"};

extern const char* signal[] = { "reg_wen","reg_ren","alu_op","mem_wen",	"mem_ren","sel1", "sel2","sel3",
"sel4","sel5","sel6","sel7","sel8","branch","auipc","lui"};     //0 index corresponding to 0th bit in controlsignal



void startdecoder::init_decode() {                                            //initialize x1 = 12, x2 =0
    ins_array[0] = 0b0000000000000001010000110000011;  // 0 loop ld x3 0(x1)    x3 = 0+x1 , x1 = 12, x3 =12       x3 = x1=8
    ins_array[1] = 0b00000000001000011000001000110011;  //1 add x4, x3, x2      x4 = x3 + x2, x2=0, 12 + 0 = 12   x4=8+0 =8
    ins_array[2] = 0b00000000010000001010000000100011;  //  2 sd x4, 0(x1)      save x4 in x1, x1 = x4 = 12       x1 = 8
    ins_array[3] = 0b11111111100000001000000010010011;  // 3 addi x1, x1, -4     x1 = x1 -4 = 12 -4 = 8           x1 = 4
    ins_array[4] = 0b11111110001000001001101111100011;  //4 bne x1, x2, loop     x1 != x2 8 != 0 
    set_reg_val(1, 20);
    set_reg_val(2, 0);
    set_reg_val(4, 0);
   // cout << dd->getOPcode(
   /* for (int i = 0; i < 5; i++) {
        inst = ins_array[i];
        InsType();
        cout << "Desc: " << desc << "rs1 :" << rs1 << " " << "rs2" << rs2 << " rd : " << rd << " imm12 :" << imm12 << endl;
    }
    cout << dd->getOPcode(ins_array[1]);
    cout << dd->getOPcode(ins_array[2]);
    cout << dd->getOPcode(ins_array[3]);
    cout << dd->getOPcode(ins_array[4]);*/

    }

  void startdecoder::InsType()
  {
  t = dd->getOPcode(inst);
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
                //rs2 = dd->getRs2();   //no rs2 in I type
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
                rd = dd->getRd();
   
                cnt = dd->getControlSignals(desc);
                 break;
    case 'J':   dd = new J_decode(inst);
                desc = dd->getFuncDesc();
               // rs1 = dd->getRs1();         //rs1 also not in j type
               // rs2 = dd->getRs2();  //Rs2 is the shiftamount bits
                rd = dd->getRd();
                imm12 = dd->getImm12();
                cnt = dd->getControlSignals(desc); 
                break;
    case 'A':   dd = new J_decode(inst);           //what is a type
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
    case 'W':   dd = new U_decode(inst);       //what is W type
                desc = dd->getFuncDesc();
                 rd = dd->getRd();
                imm20 = dd->getImm20();
                 cnt = dd->getControlSignals(desc); 
                break;

    }
}
  int startdecoder::increment_pc(uint16_t i)
  { 
      if ((pc + i) < INSMAX) pc = pc + i;
      else
          return INSMAX;
      return pc;
  }
  uint32_t startdecoder::get_reg_val(uint8_t rg)
  {
      return registers[rg];
  }
  int startdecoder::get_pc()
  {
      return pc;
  }
  void startdecoder::set_reg_val(uint8_t rg, int val)
  {
      registers[rg] = val;
  }
  void startdecoder::set_pc(uint32_t ins_addr)
  {
      pc = ins_addr;
  }
  int startdecoder::check_depend(int r1, int r2, int r3)
  {
      log << "in check_depend, reg" << r1 << " " << r2 << " " << r3 << "\n";
      //if case if we have same registers like rs1 is 1 and rs2 is also 1, then we need to check once only
      //to eleminate any repeated reg, i am using a set
      set<int> reg_set;
      reg_set.insert(r1);
      reg_set.insert(r2);
      reg_set.insert(r3);
      
      bool all_reg = false;
      for (auto it = reg_set.begin(); it != reg_set.end(); ++it)
      {
          if ((*it) < 0) continue;

          if (bool_reg[*it] == false) all_reg = true;
          else
          {
              all_reg = false;
              break;
          }
      }
      if (all_reg)  //all regs are available, no dependencies, ret 0
      {
          cout << "all true ";
          for (auto it = reg_set.begin(); it != reg_set.end(); ++it)
          {
              if ((*it) < 0) continue;

              bool_reg[*it] =true;
          }
          return 0;
      }
      else
          return 1;
  }

int startdecoder::check_depend(int rg)
{
    log << "in check_depend, reg" << rg << "\n";
    if (rg >= 0 && rg < 32 && bool_reg[rg] == false) {
        bool_reg[rg] = true;
        log << "register made true\n";
        return 0;
    }
    else if (rg < 0) return 0;
    else
        return 1;

}
int startdecoder::ALu_decode(op_val& op)
{
    //check the inst type and get all operands also check for any offset dependencies
    int imm_offset;
    log << "alu decode enter\n";
    switch (op.c_desc)
    {
    case 0:    //add ---> get rs1 value, rs2 value and add. send res to rd
        bool_reg[op.rs1] = false;
        bool_reg[op.rs2] = false;
      //  decode_Q.push(op);
        break;
    case 1:    //addi  
        if (op.rd != op.rs1)
            bool_reg[op.rs1] = false;

        //hard coded for this example
        op.c_imm12_val = -4;
       // decode_Q.push(op);
        break;
    case 4:     //lw function : load the rd register from offset calculated reg
        imm_offset = op.rs1 + op.c_imm12_val;    //see if this reg is free
        if (imm_offset != op.rs1)         //if offset if 0 then it is same reg and already checked in fetch
        {
            // if (check_depend(imm_offset) == 0) {
            if (bool_reg[imm_offset] == false) {
                op.c_imm12_val = get_reg_val((uint8_t)imm_offset);    //get the value to be load into rd and saved in c_imm12_val for alu
               // bool_reg[imm_offset] = false;      //release the register after reading its value
             //   decode_Q.push(op);
            }
            else
            {
                return 0;
            }
        }
        else
        {
            op.c_imm12_val = get_reg_val((uint8_t)imm_offset);    //get the value to be load into rd and saved in c_imm12_val for alu
            bool_reg[imm_offset] = false;      //release the register after reading its value
          //  decode_Q.push(op);
            // msg = msg + "decode " + codeDesc[op.c_desc] + " " + to_string(op.rd) + " " + to_string(op.c_imm12_val) + "  ";
        }
        break;
    case 5:     //sw store func : save the value of rs2 into calculated reg address
        imm_offset = op.rs1 + op.c_imm12_val;
        if (imm_offset != op.rs1) {
            if (check_depend(imm_offset) == 0) {
                op.c_imm12_val = imm_offset;    //address of the destination register is calculated and saved for alu
                op.rs2_val = get_reg_val(op.rs2);   //rs2 value is saved and rs2 can be released
                bool_reg[op.rs2] = false;
              //  decode_Q.push(op);
                //   msg = msg + "decode " + codeDesc[op.c_desc] + " " + to_string(op.rs2) + " " + to_string(op.c_imm12_val) + "  ";
            }
            else return 0;
        }
        else
        {
            op.c_imm12_val = imm_offset;    //address of the destination register is calculated and saved for alu
            op.rs2_val = get_reg_val(op.rs2);   //rs2 value is saved and rs2 can be released
            bool_reg[op.rs2] = false;
           // decode_Q.push(op);
            // msg = msg + "decode " + codeDesc[op.c_desc] + " " + to_string(op.rs2) + " " + to_string(op.c_imm12_val) + "  ";
        }

        break;
    case 30:    //bne function
       
          //decode_Q.push(op);
          //msg = msg + "decode " + codeDesc[op.c_desc] + " " + to_string(op.rs1_val) + " " + to_string(op.rs2_val) + "  ";
          break;
      }
      
       return 1;  
  }
  int startdecoder::Fetch()
  {
      op_val op = {0};
      op_val p = { 0 };
      p.c_desc = -1;
          log << "fetch start\n";
          if (Dep == 0) { // no dependency of registers
              log << "dep = 0 \n";
              inst = ins_array[pc];
              if (get_pc() >= INSMAX) {
                  set_pc(0);
              }
              increment_pc(1);
              rs1 = rs2 = rd = -1;
              InsType();
              log <<desc <<"rs1: " << rs1 << " " << rs2 << " " << rd << "imm12 "<<imm12<< "\n";
              log << "InsType end\n";
          }
          
          if (check_depend(rs1, rs2, rd) == 0) // && check_depend(rs2) == 0 && check_depend(rd)==0)
          {              
              log << "check-depend return 0" << rs1 <<" "<< rs2<<" "<<rd<<endl;
              Dep = 0;

              //pack the inst details
              op.rs1 = rs1;  op.rs2 = rs2;   op.rd = rd;
              op.rs1_val = get_reg_val(rs1); rs1_val = op.rs1_val;   op.rs2_val = get_reg_val(rs2); rs2_val = op.rs2_val;
              op.rd_val = get_reg_val(rd);  rd_val = op.rd_val;
              op.c_desc = desc; 

              //if branch then loop back to the first inst 0. this is hard coded for this example
              if(desc == 30)
               op.c_imm12_val = 0; 

              //if addi then imm value is -4, hard coded for this example, don't know to represent -ve imm values in mech code
              if(desc == 1)  op.c_imm12_val = -4;   

              op.c_imm20_val = 0;//imm20;   //hard coded imm20 as this is not using in this example

              //push the record in fetch queue
              log << "pushed in fetch " << desc << endl;
              if (fetch_Q.empty()) 
              {
                  if(clk>1)
                  fetch_Q.push(p); 
              } //first queue will be empty , then before fetch wpnt it push NOP?
              fetch_Q.push(op);

              fet_sucess = 1;
             // rs1 = rs2 = rd = -1;
              if (desc >= 28 && desc <= 33)   //for all branch operations feed the pc with the branch address hardcoded
              {
                //  pc = pc + imm12; 
                  pc = 0;      //this if for our current application 
              }
          }     //end of if no dependency 
          else {
              fet_sucess = 0;
              Dep = 1;
            }
          return fet_sucess;
   }

  int startdecoder::execute(op_val& op)
  {
      log << "in execution\n";
      op_val p = { 0 };
      p.c_desc = -1;
      switch (op.c_desc)
      {
      case 0:    //add ---> get rs1 value, rs2 value and add. send res to rd
          op.rd_val = op.rs1_val + op.rs2_val;
          exe_Q.push(op);    //the rd_val to be written in the rd register by write_back func, so put in the queue
          log << "exec pushed " << op.c_desc << endl;
          log << "add execute\n";
          return 1;
         // break;

      case 1:    //addi  
          log << "addi " << "rd:"<< op.rd <<" " << op.rs1_val << op.c_imm12_val;
           op.rd_val = op.rs1_val + op.c_imm12_val;
           exe_Q.push(op);       //the rd_val to be written in the rd register by write_back func, so put in the queue
           log << "addi execute\n";
           return 1;
          //break;

      case 4:     //lw function   load rd with the value in c_imm12_val which is already calculated by alu_decode
        // set_reg_val(op.rd, op.c_imm12_val);
         // bool_reg[op.rd] = false;
          op.rd_val = op.c_imm12_val;
          exe_Q.push(op);    //push an empty struct so that writeback will get nope  
          log << "lw execute\n";
          return 1;
        //  break;

      case 5:     //sw store func
         // set_reg_val(op.c_imm12_val, op.rs2_val);   //store the value of rs2 at the reg given by c_imm12_val
          //bool_reg[op.c_imm12_val] = false;
          op.rd = op.c_imm12_val;
          op.rd_val = op.rs2_val;
         
          exe_Q.push(op);
          log << "sw execute\n";
          return 1;
          break;

      case 30:    //bne function
          log << "bne: " << op.rs1_val << " " << op.rs2_val << endl;
          if (op.rs1_val == op.rs2_val) {         //print the message and flush all queues(here queues will be deleted automatically ) exit
              //return 0;
              log << "bne execute\n";
             // end_process(0);
            //  exit(0);
              return 3;
          }
          else
          {
              bool_reg[op.rs1] = false;
              bool_reg[op.rs2] = false;
             
              exe_Q.push(p);
              log << "bne execute\n";
              return 1;
          }
        
         }
      return 0;
  }

  void startdecoder::start_process() 
  {
      operand_val op_d, op_e, op_wb;
      int deco_sucess=1, deco_dep=0, ex_sucess=1, ex_dep=0;
      fet_sucess = 1; int  done = 1;
      clk = 0; Dep = 0;
      log << "process started\n";
      while (done) {
          clk++;
          msg = msg + "clock :" + to_string(clk);
              log << "fetch called\n";
             fet_sucess= Fetch();
             if (fet_sucess)// no differentiation for add, 
                 msg = msg + " fetch (" + codeDesc[desc] +" " + to_string(get_reg_val(rs1)) + " " + to_string(get_reg_val(rs2)) + " " + to_string(get_reg_val(rd)) + ") ";
             else {
                 msg = msg + " fetch (" + codeDesc[desc] + " " + to_string(get_reg_val(rs1)) + " " + to_string(get_reg_val(rs2)) + " " + to_string(get_reg_val(rd)) + ") ";

               // msg = msg + "fetch (" + codeDesc[desc] + " " + to_string(rd_val) + " " + to_string(rs1_val) + " " + to_string(rs2_val) + ")";
                //msg = msg + "fetch (NOPE) ";
             }
              log << " fetch end\n";
            
         //decoding

              if (clk <= 1) { msg += "\n"; continue; }

              if (!fetch_Q.empty() && deco_dep == 0)
              {
                  op_d = fetch_Q.front();
                  fetch_Q.pop();
                  if (op_d.c_desc >= 0)
                  {
                      log << "read form fetch\n";
                      deco_sucess = ALu_decode(op_d);
                      if (deco_sucess)  //sucessful, no depend
                      {
                          deco_dep = 0;
                          decode_Q.push(op_d);
                          msg = msg + " decode (" + codeDesc[op_d.c_desc] + " " + to_string(get_reg_val(rs1)) + " " + to_string(get_reg_val(rs2)) + " " + to_string(get_reg_val(rd)) +  ") ";
                         // msg = msg + "decode (" + codeDesc[op_d.c_desc] + ") "; // print the values op_d.rs1_val
                      }
                      else
                      {    //if dependencies then push null record
                          deco_dep = 1;
                          op_val p = { 0 };
                          p.c_desc = -1;
                          decode_Q.push(p);
                        //   msg = msg + "decode (" + codeDesc[op_d.c_desc] + ") ";
                          msg = msg + " decode (NOPE) ";
                      }
                  }   //end of if not a null record from fetch Q

                  else
                  {   //null record received,push it to decode Q
                      log << " decode null received\n";
                      op_val p = { 0 };
                      p.c_desc = -1;
                      decode_Q.push(p);
                      msg = msg + " decode (NOPE) ";
                  }
              }
              else if (deco_dep == 1)
              {
                  log << "decode depend\n";
                  deco_sucess = ALu_decode(op_d);
                  if (deco_sucess) //dependencies cleared
                  {
                      log << "depend cleared\n";
                      deco_dep = 0;
                      decode_Q.push(op_d);
                      msg = msg + " decode (" + codeDesc[op_d.c_desc] + " "  + to_string(get_reg_val(rs1)) + " " + to_string(get_reg_val(rs2)) + " " + to_string(get_reg_val(rd)) + ") ";
                      //msg = msg + "decode (" + codeDesc[op_d.c_desc] + ") ";
                  }
                  else  //dependencies not cleared so push a null record in the queue
                  {
                      log << "dep not cleared\n";
                      deco_dep = 1;
                      op_val p = { 0 };
                      p.c_desc = -1;
                      decode_Q.push(p);
                      // msg = msg + "decode (" + codeDesc[op_d.c_desc] + ") ";
                      msg = msg + " decode (NOPE) ";
                  }
              }
              else
              {                        
                   //if the fetch Q is null
                      //to be implemented
                      op_val p = { 0 };
                      p.c_desc = -1;
                      decode_Q.push(p);
                      msg = msg + " decode (NOPE) ";
                  }
               log << "decode end\n";
          //executing 
          if (clk <= 2) { msg += "\n"; continue; }

          if ( !decode_Q.empty() )
          {                
              op_e = decode_Q.front();
              decode_Q.pop();
              log << "execute called:  "<<op_e.c_desc<<"\n";
              if (op_e.c_desc >= 0)
              {                 
                  ex_sucess = execute(op_e);
                  if (ex_sucess == 1 ) {
                      msg = msg + " execute (" + codeDesc[op_e.c_desc] + " " + to_string(get_reg_val(rs1)) + " " + to_string(get_reg_val(rs2)) + " " + to_string(get_reg_val(rd)) + ") ";
                      // msg = msg + "execute (" + codeDesc[op_e.c_desc] + ") "; // values op_e.rs
                  }
                  else if(ex_sucess == 3){
                      msg = msg + " execute (" + codeDesc[op_e.c_desc] + ") " + "Flush the pipeline";
                      msg += "\n";
                      msg = msg + "clock :97 fetch (NOP) decode (NOP) execute (NOP) write-back (NOP) Program exit. ";
                      msg += "\n";
                      simu.push(msg);
                      end_process(0);
                      done = 0;
                      return;
                  }
                
                  else {   //ex_sucess is 0, not sucessful  but execute will not return 0 and this will not be exe
                      // = msg + "execute (" + codeDesc[op_e.c_desc] + ")";
                      msg = msg + " execute (" + codeDesc[op_e.c_desc] + " " + to_string(get_reg_val(rs1)) + " " + to_string(get_reg_val(rs2)) + " " + to_string(get_reg_val(rd)) + ") ";
                      op_val p = {0};
                      p.c_desc = -1;
                      exe_Q.push(p);
                  }
              }   //end of c_desc >= 0
             else
              {
                  msg += " execute (NOPE) ";
                  op_val p = { 0 };
                  p.c_desc = -1;
                 exe_Q.push(p);
              }
           }  // end of not empty if
          else
          {
              msg += " execute (NOPE) ";
              op_val p = {0};
               p.c_desc = -1;
               exe_Q.push(p);
           }
          
          log << "execute end\n";
          if (clk <= 3) { msg += "\n"; continue; };
          if ( !exe_Q.empty())
          {
              log << "write back called\n";
              op_wb = exe_Q.front();
              exe_Q.pop();
              if (op_wb.c_desc >= 0) {
                  write_back(op_wb);
                  msg = msg + " write_back (" + codeDesc[op_wb.c_desc] + " " + to_string(get_reg_val(rs1)) + " " + to_string(get_reg_val(rs2)) + " " + to_string(get_reg_val(rd)) + ") ";
                 // msg = msg + "write_back (" + codeDesc[op_wb.c_desc] + ")";
              }
              else
              {
                  msg = msg + " write_back(NOPE ) ";
              }
          }
          else
          {
              msg = msg + "write_back(NOPE )";
          }
          log << "write back end\n";
         // clk++;
          msg = msg + "\n";
          simu.push(msg);
         // cout << msg;
          msg = "";
          if (fetch_Q.empty() && decode_Q.empty() && exe_Q.empty()) {
              log << "all queues empty\n";
            //  done = 0;
          }
        }
  }
  void startdecoder::write_back(op_val op)
  {
      //write back rd and release it
      set_reg_val(op.rd, op.rd_val);
      bool_reg[op.rd] = false;
     // return 1;
     }

  void startdecoder::end_process(int e)
  {
      if (e == 0) {
          cout << "program executed sucessfully with return code: " << e <<endl;
          cycle << "program executed sucessfully with return code: " << e<<endl;
          while (!simu.empty()) {
           cout<<  simu.front()<<endl;
           cycle << simu.front() << endl;
           simu.pop();
          }
      }
      else
          cout << "Program ended with error code :" << e;
      cycle << "Program ended with error code :" << e;
  }

  void startdecoder::printInstDescription() {
      if (t == 'W')
      {
          log << "Opcode Type: " << "U" << endl;
      }
      else if (t == 'A')
      {
          log << "Opcode Type: " << "J" << endl;
      }
      else
      log << "Opcode Type: " << t << endl;
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

  
