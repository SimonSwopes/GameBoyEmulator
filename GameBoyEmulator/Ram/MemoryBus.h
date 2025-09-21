#pragma once
#include <cstdint>
#include "Register.h"

namespace Ram
{
	class MemoryBus
	{
		public:

			uint8_t read(uint16_t address) const { return memory[address]; }
			uint16_t read16(uint16_t address) const { return (memory[address + 1] << 8) | memory[address]; }
			void write(uint16_t address, uint8_t value) { memory[address] = address > 0x00FF ? value : memory[address]; } // First 256 bytes bootstrap ROM
			void write(uint16_t address, uint16_t value);

		private:
			uint8_t memory[0xFFFF];

	};
}

