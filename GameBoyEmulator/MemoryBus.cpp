#include "MemoryBus.h"

namespace Ram
{

	void MemoryBus::write(uint16_t address, uint16_t value)
	{
		if (address > 0x00FF)
		{
			memory[address] = value & 0x00FF;
			memory[address + 1] = value >> 8;
		}
	}
}
