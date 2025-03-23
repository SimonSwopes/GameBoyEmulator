#pragma once
#include <cstdint>;
namespace CPU
{
	class ControlUnit
	{
		public:
			ControlUnit() : alu(), memory(), p(), c(), pc(p, c) {}

		private:
			Register_uint16 pc;
			Register_unint8 p;
			Register_unint8 c;
			ArithmeticLogicUnit alu;
			Ram::MemoryBus memory;

			void step();
			void decode(uint8_t opcode);
			void decodeCBIns();
	};
}
