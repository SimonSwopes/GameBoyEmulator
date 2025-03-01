#include "ArithmeticLogicUnit.h"

namespace CPU {
#pragma region 8BitArithmetic


	void ArithmeticLogicUnit::ADD(uint8_t value)
	{
		uint8_t result = getA() + value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag((getA() & 0x0F) + (value & 0x0F) > 0x0F);
		setCarryFlag(result < getA());
		setA(result);
	}
	void ArithmeticLogicUnit::ADD(ArithmeticTargetRegister reg) { ADD(reg.get()); }

	void ArithmeticLogicUnit::ADC(uint8_t value)
	{
		uint8_t carry = getCarryFlag();
		uint8_t result = getA() + value + getCarryFlag();
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag((getA() & 0x0F) + (value & 0x0F) + getCarryFlag() > 0x0F);
		setCarryFlag(result < getA() || (result == getA() && carry));
		setA(result);
	}
	void ArithmeticLogicUnit::ADC(ArithmeticTargetRegister reg) { ADC(reg.get()); }

	void ArithmeticLogicUnit::SUB(uint8_t value)
	{
		uint8_t result = getA() - value;
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (value & 0x0F));
		setCarryFlag(result > getA());
		setA(result);
	}
	void ArithmeticLogicUnit::SUB(ArithmeticTargetRegister reg) { SUB(reg.get()); }

	void ArithmeticLogicUnit::SBC(uint8_t value)
	{
		uint8_t carry = getCarryFlag();
		uint8_t result = getA() - value - getCarryFlag();
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (value & 0x0F) + getCarryFlag());
		setCarryFlag(result > getA() || (result == getA() && carry));
		setA(result);
	}
	void ArithmeticLogicUnit::SBC(ArithmeticTargetRegister reg) { SBC(reg.get()); }
#pragma endregion

#pragma region 8BitLogical
	void ArithmeticLogicUnit::AND(uint8_t value)
	{
		uint8_t result = getA() & value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(true);
		setCarryFlag(false);
		setA(result);
	}
	void ArithmeticLogicUnit::AND(ArithmeticTargetRegister reg) { AND(reg.get()); }

	void ArithmeticLogicUnit::OR(uint8_t value)
	{
		uint8_t result = getA() | value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}
	void ArithmeticLogicUnit::OR(ArithmeticTargetRegister reg) { OR(reg.get()); }

	void ArithmeticLogicUnit::XOR(uint8_t value)
	{
		uint8_t result = getA() ^ value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}
	void ArithmeticLogicUnit::XOR(ArithmeticTargetRegister reg) { XOR(reg.get()); }
#pragma endregion
}