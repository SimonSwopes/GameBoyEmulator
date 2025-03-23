#pragma once
#include <cstdint>

namespace Ram
{
	class MemoryBus
	{
		public:
	
			uint8_t read(uint16_t address) const { return memory[address]; }
			void write(uint16_t address, uint8_t value) { memory[address] = address > 0x00FF ? value : memory[address]; } // First 256 bytes bootstrap ROM

		private:
			uint8_t memory[0xFFFF];

	};
}

