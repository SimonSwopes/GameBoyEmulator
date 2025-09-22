#pragma once
#include <cstdint>
#include "Register.h"

namespace Ram
{
	class MemoryBus
	{
		public:
            MemoryBus() {
                for (int i = 0; i < 0xFFFF; i++) {
                    memory[i] = 0;
                }
                
                memory[0xFF0F] = 0;  // Interrupt Flag (IF)
                memory[0xFFFF] = 0;  // Interrupt Enable (IE)
            }

			uint8_t read(uint16_t address) const { return memory[address]; }
			uint16_t read16(uint16_t address) const { return (memory[address + 1] << 8) | memory[address]; }
			void write(uint16_t address, uint8_t value) { memory[address] = address > 0x00FF ? value : memory[address]; } // First 256 bytes bootstrap ROM
			void write(uint16_t address, uint16_t value);
            

            void requestInterrupt(uint8_t interruptBit) {
                memory[0xFF0F] |= (1 << interruptBit);
            }

            static const uint8_t VBLANK_INTERRUPT = 0;
            static const uint8_t LCD_STAT_INTERRUPT = 1;
            static const uint8_t TIMER_INTERRUPT = 2;
            static const uint8_t SERIAL_INTERRUPT = 3;
            static const uint8_t JOYPAD_INTERRUPT = 4;

		private:
			uint8_t memory[0xFFFF];
	};
}

