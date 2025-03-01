#include "RegisterFile.h"

#pragma once
namespace CPU {

	class ArithmeticLogicUnit : RegisterFile
	{

		public:
			ArithmeticLogicUnit() : RegisterFile() {}

			// 8 bit arithmetic
			void ADD(uint8_t value);
			void ADD(ArithmeticTargetRegister reg);
			void ADC(uint8_t value);
			void ADC(ArithmeticTargetRegister reg);
			void SUB(uint8_t value);
			void SUB(ArithmeticTargetRegister reg);
			void SBC(uint8_t value);
			void SBC(ArithmeticTargetRegister reg);

			// 8 bit logical
			void AND(uint8_t value);
			void AND(ArithmeticTargetRegister reg);
			void OR(uint8_t value);
			void OR(ArithmeticTargetRegister reg);
			void XOR(uint8_t value);
			void XOR(ArithmeticTargetRegister reg);
	};
}