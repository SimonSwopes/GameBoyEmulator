#include "ArithmeticLogicUnit.h"

namespace CPU {

	void ArithmeticLogicUnit::INC(Register_uint16 reg)
	{
		uint16_t result = reg.get() + 1;
		reg.set(result);
	}

	void ArithmeticLogicUnit::DEC(Register_uint16 reg)
	{
		uint16_t result = reg.get() - 1;
		reg.set(result);
	}
}