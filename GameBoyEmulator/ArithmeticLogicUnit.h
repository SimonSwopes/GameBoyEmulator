#include "RegisterFile.h"

#pragma once
namespace CPU {

	class ArithmeticLogicUnit : RegisterFile
	{

		public:
			ArithmeticLogicUnit() : RegisterFile() {}

			// 8 bit arithmetic
			void ADD();
			void ADD(uint8_t value);
			void ADD(ArithmeticTargetRegister_unint8 reg);

			void ADC();
			void ADC(uint8_t value);
			void ADC(ArithmeticTargetRegister_unint8 reg);

			void SUB();
			void SUB(uint8_t value);
			void SUB(ArithmeticTargetRegister_unint8 reg);

			void SBC();
			void SBC(uint8_t value);
			void SBC(ArithmeticTargetRegister_unint8 reg);

			// 8 bit logical
			void AND();
			void AND(uint8_t value);
			void AND(ArithmeticTargetRegister_unint8 reg);
			void OR();
			void OR(uint8_t value);
			void OR(ArithmeticTargetRegister_unint8 reg);
			void XOR();
			void XOR(uint8_t value);
			void XOR(ArithmeticTargetRegister_unint8 reg);
			void CP();
			void CP(uint8_t value);
			void CP(ArithmeticTargetRegister_unint8 reg);

			// 8 Bit INC/DEC
			void INC();
			void INC(ArithmeticTargetRegister_unint8 reg);
			void DEC();
			void DEC(ArithmeticTargetRegister_unint8 reg);

			void CPL();
			// May need to come back and DAA in the future if working with BCD

			// 16 bit arithmetic
			void ADD(ArithmeticTargetRegister_unint16 reg);
			void ADD(int8_t);
			void INC(ArithmeticTargetRegister_unint16 reg);
			void DEC(ArithmeticTargetRegister_unint16 reg);
			void LD(int8_t value);
	};
}