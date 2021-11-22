#include "decoder.h"

char decoder::getOPcode()
{
    uint8_t op;
    op = (inst);
    if (((op & 0b00110011) == 0b00110011) && ((op & 0b00000111) == 0b00000011)) return 'R';
    if (((op & 0b00010011) == 0b00010011) && ((op & 0b00000111) == 0b00000011))  return 'I';
    if (((op & 0b00010111) == 0b00010111) && ((op & 0b00110000) == 0b00010000)) return 'U';
    if ((op & 0b00110111) == 0b00110111) return 'W';
    if ((op & 0b1100011) == 0b1100011) return 'B';//01100010
    if ((op & 0b0100011) == 0b0100011) return 'S';
    if ((op & 0b0000011) == 0b0000011) return 'L';
  
   if ((op & 0b01110000) == 0b01110000) return 'J';
   if ((op & 0b00110000) == 0b00110000) return 'A';
    return '\0';
}

char decoder::getOPcode(uint32_t ins)
{
    inst = ins;
    return getOPcode();
}

uint8_t  decoder::getFun3() {
    uint8_t fun3;
    fun3 = (uint8_t)((inst & 0b00000000000000000111000000000000) >> 12);
    return fun3;
}

uint8_t decoder::getFun7() {
    uint8_t fun7;
    fun7 = (uint8_t)((inst & 0b11111110000000000000000000000000) >> 25);
    return fun7;

}

uint8_t decoder::getRd()
{
    uint8_t rd;
    rd = (uint8_t)((inst & 0b00000000000000000000111110000000)>>7);
    return rd;
}

uint8_t decoder::getRs1()
{
    uint8_t rs1;
    rs1 = (uint8_t)((inst & 0b00000000000011111000000000000000) >> 15);
    return rs1;
}

uint8_t decoder::getRs2()
{
    uint8_t rs2;
    rs2 = (uint8_t)((inst & 0b00000001111100000000000000000000 )>> 20);
    return rs2;
}

uint16_t decoder::getControlSignals(int desc)
{
        return 0;
}

int decoder::getFuncDesc()
{
    return 0;
}

uint16_t decoder::getImm12()
{
    return 0;
}

uint32_t decoder::getImm12b()
{
    return 0;
}

uint32_t decoder::getImm20()
{
    return 0;
}
