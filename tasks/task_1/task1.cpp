#include <iostream>
#include <stdint.h>
#include <iomanip>

uint32_t getbitsfromuint32(uint32_t inputValue,unsigned bitOffset,unsigned bitLength)
{
	unsigned mask;
	mask = (1UL<<bitLength)-1;
	uint32_t isolatedXbits = mask & (inputValue>>bitOffset);

	return isolatedXbits;
}

int main()
{
	uint32_t res = getbitsfromuint32(0xABCDEF12, 4, 12);

	std::cout << "0x" << std::setfill('0') << std::setw(8) <<std::hex << res << std::endl;
}
