#include "TypeDecoders.h"
/* "add=0", "addi", "sub", "mul", "lw", "sw=5", "sb", "lh", "lb", "sh", "lui" and=10", "or", "nor", "xor", "andi",
"ori=15", "xori", "sll", "sra", "srl", "sltu=20", "slt", "sltiu", "slti", "slli", "srai=25", "srli",
"movn", "bgeu", "beq", "bne=30", "bge", "bltu", "blt", "j", "jalr=35", "jal", "and","lbu", "lhu" ,"mul=40","mulh","mulhsu","mulhu",
"div","divu","rem","remu","auipc"};
*/
int I_decode::getFuncDesc() {
    uint16_t f7 = getFun7();
    uint8_t f3 = getFun3();
    switch (f3) {
    case 0: return 1;   //addi
    case 2: return 23;  //slti
    case 3: return 22;   //sltiu
    case 4: return 16;  //xori
    case 6: return 15;  //ori
    case 7: return 14;   //andi

    case 1: return 24;   //slli
    case 5:   if (f7 == 0)   return 26;    //srli
                  else if ((f7 >> 5) == 1) return  25;  //"srai
                      else  cout << "this funciont is not defined/implemented";
        break;

    default:  cout << "this funciont is not defined/implemented";
   }
    return 0;
}

uint16_t I_decode::getControlSignals(int desc) {
    int cnt = desc;     //getFuncDesc();
    switch (cnt) {
    case 1:        //addi rd,rs1,imm
    case 14:       //andi rd,rs1,imm
    case 15:       //ori rd,rs1,imm
    case 16:       //xori rd,rs1,imm
    case 22:       //sltiu rd,rs1,imm
    case 23:       //slti rd,rs1,imm
             return(0b1110011000100010);
             break;
    case 24:    //slli rd,rs1,shamt
     case 26:      //srli rd,rs1,shamt
     case 25:       //srai rd,rs1,shamt   
         break;
    default:   cout << "this funciont is not defined/implemented";
        return 0;
    }
    return 0;
}

uint16_t I_decode::getImm12()
{
    uint16_t f7 = getFun7();
    uint8_t r = getRs2();
    uint16_t imm;
    imm = r;
    imm = (f7 << 5) | imm;
    // 12 bit imm having sign bit in 11th position
    //mask imm with 1 shifted to 11th pos to check if it is 1     
    if (imm & (1 <<10)) {
        imm = imm | 0b1111000000000000; //sign extension
       }
    return imm;
}

int R_decode::getFuncDesc()
{
    uint8_t f3 = getFun3();
    uint8_t f7 = getFun7();

    if (f3 == 0 && f7 == 0) return 0;    //add
    if (f3 == 0 && f7 == 32)return 2;   //sub
    if (f3 == 1 && f7 == 0) return 17;   //sll
    if (f3 == 2 && f7 == 0) return 21;   //slt
    
    if (f3 == 3 && f7 == 0) return 20;   //sltu
    if (f3 == 4 && f7 == 0) return 13;   //xor
    if (f3 == 5 && f7 == 0) return 19;   //srl
    if (f3 == 5 && f7 == 32) return 18;  //sra
    if (f3 == 6 && f7 == 0) return 11;   //or
    if (f3 == 7 && f7 == 0) return 37; //and

    if (f7 == 1 && f3 == 0) return 40; //mul
    if (f7 == 1 && f3 == 1) return 41; //mulh
    if (f7 == 1 && f3 == 2) return 42; //mulhsu
    if (f7 == 1 && f3 == 3)return  43; //mulhu
    if (f7 == 1 && f3 == 4)return 44;  //div
    if (f7 == 1 && f3 == 5)return 45;  //divu
    if (f7 == 1 && f3 == 6)return 46;  //rem
    if (f7 == 1 && f3 == 7)return 47;  //remu
    return 0;
}
uint16_t R_decode::getControlSignals(int desc) {
    int cnt = desc;    // getFuncDesc();
        switch (cnt) {
        case 0:         //add
        case 2:         //sub
        case 17:        //sll
        case 21:        //slt
        case 20:        //sltu
        case 13:        //xor
        case 19:        //srl
        case 18:        //sra
        case 11:        //or
        case 37:        //and
        case 40:        //mul
        case 41:      //mulh
        case 42:       //mulhsu
        case 43:       //mulhu
        case 44:       //div
        case 45:       //divu
        case 46:       //rem
        case 47:       //remu
                     return(0b1110000000100000);
                     break;  
        default:   cout << "this funciont is not defined/implemented";
            return 0;
      }

    }

int S_decode::getFuncDesc()
{
    uint8_t f3 = getFun3();
   // uint8_t f7 = getFun7();
    switch (f3) {
    case 0:    return 6;     //sb rs2,imm(rs1)

    case 1:    return 9;    //sh rs2,imm(rs1)
    case 2:    return 5;     //sw rs2, imm(rs1)
        break;
    default:  cout << "this funciont is not defined/implemented";
         }
    return 0;
}

uint16_t S_decode::getControlSignals(int desc)
{
    int cnt = desc;   // getFuncDesc();
    switch (cnt) {
    case 6:             //sb rs2,imm(rs1)

    case 9:            //sh rs2,imm(rs1)
    case 5:             //sw rs2, imm(rs1)
                 return(0b1111011000101010);
                 break;  // get control signals
    default:  cout << "this funciont is not defined/implemented";
    }
    return 0;
}

uint16_t S_decode::getImm12()
{
    uint16_t imm;
    uint16_t f7 = getFun7();
    uint8_t rgd = getRd();
    imm = rgd;
    imm = imm | (f7 << 5);
    // 12 bit imm having sign bit in 11th position
    //mask imm with 1 shifted to 11th pos to check if it is 1     
    if (imm & (1 << 10)) {
        imm = imm | 0b1111000000000000; //sign extension
    }
    return imm;
}

int L_decode::getFuncDesc()
{
    uint8_t f3 = getFun3();
    switch (f3) {
    case 0: return 8;   //lb rd,imm(rs1)
    case 1: return 7;  //lh rd,imm(rs1)
    case 2: return 4;  //lw rd,imm(rs1)
    case 3: return 38;  //lbu rd,imm(rs1)
    case 4: return 39;  //lhu rd,imm(rs1)
    default:   cout << "this funciont is not defined/implemented";
    }
    return 0;
}

uint16_t L_decode::getControlSignals(int desc)
{
    int cnt = desc;  // getFuncDesc();
    switch (cnt) {
    case 8:     //lb           //return the control signals for each case;
    case 7:     //lh
    case 4:     //lw
    case 38:     //lbu
    case 39:     //"get control signals\n";    //lhu
                 return(0b1111111100110010);
                 break;
    default:  cout << "this funciont is not defined/implemented";
    }
    return 0;
}

uint16_t L_decode::getImm12()
{
    uint16_t f7 = getFun7();
    uint8_t r = getRs2();
    uint16_t imm;
    imm = r;
    imm = (f7 << 5) | imm;
    // 12 bit imm having sign bit in 11th position
    //mask imm with 1 shifted to 11th pos to check if it is 1     
    if (imm & (1 << 10)) {
        imm = imm | 0b1111000000000000; //sign extension
    }
    return imm;
}

int B_decode::getFuncDesc()
{
    uint8_t f3 = getFun3();
    switch (f3) {
    case 0: return 29;   //beq rs1,rs2,pcrel 13
    case 1: return 30;  //bne rs1,rs2,pcrel 13
    case 4: return 33;  //blt rs1,rs2,pcrel 13
    case 5: return 31;  //bge rs1,rs2,pcrel 13
    case 6: return 32;  //bltu rs1, rs2, pcrel 13
    case 7: return 28;  //bgeu rs1,rs2,pcrel 13
    break;
    default:  cout << "this funciont is not defined/implemented";
    break;
    }
    return 0;
}

uint16_t B_decode::getControlSignals(int desc)
{
    int cnt = desc;  // getFuncDesc();
    switch (cnt) {
    case 29 :  //beq rs1,rs2,pcrel 13
    case 30 : //bne rs1,rs2,pcrel 13
    case 33 : //blt rs1,rs2,pcrel 13
    case 31 : //bge rs1,rs2,pcrel 13
    case 32 : //bltu rs1, rs2, pcrel 13
    case 28 : //bgeu rs1,rs2,pcrel 13
               return(0b0110000000100100);
        break;
    default:  cout << "this funciont is not defined/implemented in B type";
    }
    return 0;
}

uint32_t B_decode::getImm12b()
{   //            12 11  10-5  4-1  0        
    //      0b000 0  0  000000 0000 0;
    
    uint32_t imm = 0;
    uint8_t f7 = getFun7();
    uint8_t rgd = getRd(); // 0000 0110
    if (f7 >> 6 == 1)
    {
        imm = 0b11111111111111111111000000000000 + (((uint32_t)(rgd << 7)) << 12) +\
            (((uint32_t)(f7 & 0b00111111)) << 11) + (uint32_t)(rgd & 0b00011110);

    }
    else if (f7 >> 6 == 0)
    {
        imm = 0b00000000000000000000000000000000 + (((uint32_t)(rgd << 7)) << 12) + \
            (((uint32_t)(f7 & 0b00111111)) << 11) + (uint32_t)(rgd & 0b00011110);

    }
    
     
   return imm;
}
int J_decode::getFuncDesc() {
    char t = getOPcode();
    switch (t) {
    case 'J': return 35;   //jalr
    break;
    case 'A': return 36;
    default:  cout << "this funciont is not defined/implemented in J type";
    break;
    }
    return 0;
}

uint16_t J_decode::getControlSignals(int desc) {
    int cnt = desc;     //getFuncDesc();
   // char t = getOPcode();
    switch (cnt) {
    case 36:        //jalr
    return(0b0110011001100010);
    break;
    case 35:        //jal
    return(0b0010011001000010);
    break;
    default:   cout << "this funciont is not defined/implemented" << endl;
        break;
    }
    return 0;
}

uint16_t J_decode::getImm12()
{
    //for jalr
    uint16_t f7 = getFun7();
    uint8_t r = getRs2();
    uint16_t imm;
    imm = r;
    imm = (f7 << 5) | imm;
    // 12 bit imm having sign bit in 11th position
    //mask imm with 1 shifted to 11th pos to check if it is 1     
    if (imm & (1 << 10)) {
        imm = imm | 0b1111000000000000; //sign extension
    }
    return imm;
}
uint32_t J_decode::getImm20()
{
    //for jal alone
    uint16_t f7 = getFun7();
    uint16_t fun3 = getFun3();
    uint8_t rs2 = getRs2();
    uint8_t rs1 = getRs1();
    uint32_t imm20 =0;
    if (f7 >> 6 == 1)
    {
        imm20 = 0b11111111111100000000000000000000 + (uint32_t)(rs1 << 15) + \
            (uint32_t)(fun3 << 12) + (((uint32_t)((rs2 << 7) << 4)) + (uint32_t)(rs2 & 0b00011110) + ((uint32_t)((fun3 & 0b0111111) << 5)));

    }
    else if (f7 >> 6 == 0)
    {
        imm20 = 0b00000000000000000000000000000000 + (uint32_t)(rs1 << 15) + \
            (uint32_t)(fun3 << 12) + (((uint32_t)((rs2 << 7) << 4)) + (uint32_t)(rs2 & 0b00011110) + ((uint32_t)((fun3 & 0b0111111) << 5)));

    }
    return imm20;
}

int U_decode::getFuncDesc() {
    char t = getOPcode();
    switch (t) {
    case 'U': return 48;   //auipc
        break;
    case 'W': return 10;   //lui
        break;
    default:  cout << "this funciont is not defined/implemented -an";
        break;
    }
    return 0;
}

uint16_t U_decode::getControlSignals(int desc) {
    int cnt = desc;     //getFuncDesc();
    switch (cnt) {
    case 48:        //auipc
        return(0b1010011000000000);
        break;
    case 10:        //lui
        return(0b1000000000000001);
        break;
    default:   cout << "this funciont is not defined/implemented" << endl;
        break;
    }
    return 0;
}
uint32_t U_decode::getImm20()
{
    uint32_t f7 = getFun7();
    uint32_t r2= getRs2();
    uint32_t r1 = getRs1();
    uint32_t f3 = getFun3();
    uint32_t imm;
    imm = f3 + (r1<<3)+(r2 <<8) +(f7<<13); 
    imm = (imm << 12);
    return imm;
}


