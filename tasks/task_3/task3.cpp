#include <iostream>
#include <vector>
#include <sstream>
#include <stdint.h>
#include <iomanip>

std::vector<bool> getBitsVector(std::string inputValue)
{
	int base = 10;
	if (inputValue.size() > 2 && inputValue[1] == 'x')
		base = 16;

	uint32_t inputNumber = std::stoul(inputValue, nullptr, base);

	std::vector<bool> bits;

	for (int i = 0; i < 32; i++)
	{
		bits.push_back(inputNumber & 1);
		inputNumber >>= 1;
	}
	return bits;
}

int main()
{
	std::vector<bool> res = getBitsVector("149");
	for (bool b : res)
	{
	     if(!b)std::cout << "false,";
		else std::cout << "true,";
	}
}
