#include <iostream>
#include <stdint.h>
#include <iomanip>
#include <sstream>

uint32_t getbitsfromuint32(const char* inputValue,unsigned bitOffset,unsigned bitLength)
{

     unsigned intvalue = std::stol(inputValue,nullptr,16);
     //uint32_t lol= 0xABCDEF12;

     //std::cout<<lol<<std::endl;
     //std::cout<<intvalue<<std::endl;

     //std::cout<<std::endl;

     unsigned mask;
     mask = (1UL<<bitLength)-1;
     uint32_t isolatedXbits = mask & (intvalue>>bitOffset);

     return isolatedXbits;
}

int main()
{
     uint32_t res = getbitsfromuint32("0xABCDEF12", 4, 12);

     std::cout << "0x" << std::setfill('0') << std::setw(8) <<std::hex << res << std::endl;
}
