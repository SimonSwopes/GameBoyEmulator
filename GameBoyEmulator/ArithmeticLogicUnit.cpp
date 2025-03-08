#include "ArithmeticLogicUnit.h"

namespace CPU {
#pragma region 8BitArithmetic

	void ArithmeticLogicUnit::ADD()
	{
		uint16_t result = getA() + getHL();
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag((getA() & 0x0F) + (getHL() & 0x0F) > 0x0F);
		setCarryFlag(result > 0xFF);
		setA(result);
	}
	void ArithmeticLogicUnit::ADD(uint8_t value)
	{
		uint8_t result = getA() + value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag((getA() & 0x0F) + (value & 0x0F) > 0x0F);
		setCarryFlag(result < getA());
		setA(result);
	}
	void ArithmeticLogicUnit::ADD(ArithmeticTargetRegister_unint8 reg) { ADD(reg.get()); }


	void ArithmeticLogicUnit::ADC()
	{
		uint16_t result = getA() + getHL() + getCarryFlag();
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag((getA() & 0x0F) + (getHL() & 0x0F) + getCarryFlag() > 0x0F);
		setCarryFlag(result > 0xFF);
		setA(result);
	}
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
	void ArithmeticLogicUnit::ADC(ArithmeticTargetRegister_unint8 reg) { ADC(reg.get()); }


	void ArithmeticLogicUnit::SUB()
	{
		uint8_t result = getA() - getHL();
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (getHL() & 0x0F));
		setCarryFlag(result > getA());
		setA(result);
	}
	void ArithmeticLogicUnit::SUB(uint8_t value)
	{
		uint8_t result = getA() - value;
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (value & 0x0F));
		setCarryFlag(result > getA());
		setA(result);
	}
	void ArithmeticLogicUnit::SUB(ArithmeticTargetRegister_unint8 reg) { SUB(reg.get()); }

	void ArithmeticLogicUnit::SBC()
	{
		uint8_t result = getA() - getHL() - getCarryFlag();
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (getHL() & 0x0F) + getCarryFlag());
		setCarryFlag(result > getA());
		setA(result);
	}
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
	void ArithmeticLogicUnit::SBC(ArithmeticTargetRegister_unint8 reg) { SBC(reg.get()); }
#pragma endregion

#pragma region 8BitLogical

	void ArithmeticLogicUnit::AND()
	{
		uint8_t result = getA() & getHL();
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(true);
		setCarryFlag(false);
		setA(result);
	}

	void ArithmeticLogicUnit::AND(uint8_t value)
	{
		uint8_t result = getA() & value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(true);
		setCarryFlag(false);
		setA(result);
	}
	void ArithmeticLogicUnit::AND(ArithmeticTargetRegister_unint8 reg) { AND(reg.get()); }

	void ArithmeticLogicUnit::OR()
	{
		uint8_t result = getA() | getHL();
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}

	void ArithmeticLogicUnit::OR(uint8_t value)
	{
		uint8_t result = getA() | value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}
	void ArithmeticLogicUnit::OR(ArithmeticTargetRegister_unint8 reg) { OR(reg.get()); }

	void ArithmeticLogicUnit::XOR()
	{
		uint8_t result = getA() ^ getHL();
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}
	void ArithmeticLogicUnit::XOR(uint8_t value)
	{
		uint8_t result = getA() ^ value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}
	void ArithmeticLogicUnit::XOR(ArithmeticTargetRegister_unint8 reg) { XOR(reg.get()); }


	void ArithmeticLogicUnit::CP()
	{
		uint8_t result = getA() - getHL();
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (getHL() & 0x0F));
		setCarryFlag(result > getA());
	}
	void ArithmeticLogicUnit::CP(uint8_t value)
	{
		uint8_t result = getA() - value;
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (value & 0x0F));
		setCarryFlag(result > getA());
	}
	void ArithmeticLogicUnit::CP(ArithmeticTargetRegister_unint8 reg) { CP(reg.get()); }
#pragma endregion	

#pragma region 8BitINC/DEC

	void ArithmeticLogicUnit::INC(ArithmeticTargetRegister_unint8 reg)
	{
		uint8_t result = reg.get() + 1;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag((reg.get() & 0x0F) == 0x0F);
		reg.set(result);
	}

	void ArithmeticLogicUnit::INC()
	{
		uint16_t result = getHL() + 1;
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag((getHL() & 0x0FFF) == 0x0FFF);
		setHL(result);
	}

	void ArithmeticLogicUnit::DEC()
	{
		uint16_t result = getHL() - 1;
		setZeroFlag(false);
		setSubtractionFlag(true);
		setHalfCarryFlag((getHL() & 0x0F) == 0x00);
		setHL(result);
	}

	void ArithmeticLogicUnit::DEC(ArithmeticTargetRegister_unint8 reg)
	{
		uint8_t result = reg.get() - 1;
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((reg.get() & 0x0F) == 0x00);
		reg.set(result);
	}

	void ArithmeticLogicUnit::CPL()
	{
		setA(getA() ^ 0xFF);
		setSubtractionFlag(true);
		setHalfCarryFlag(true);
	}

#pragma endregion

#pragma region 16BitArithmetic
	void ArithmeticLogicUnit::ADD(ArithmeticTargetRegister_unint16 reg)
	{
		uint16_t result = getHL() + reg.get();
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag((getHL() & 0x0FFF) + (reg.get() & 0x0FFF) > 0x0FFF);
		setCarryFlag(result > 0xFFFF);
		setHL(result);
	}
	void ArithmeticLogicUnit::ADD(int8_t value)
	{
		int16_t sp = static_cast<int16_t>(getSP());
		int16_t result = sp + value;
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag(((sp & 0x0F) + (value & 0x0F)) > 0x0F);
		setCarryFlag(((sp & 0xFF) + (value & 0xFF)) > 0xFF);
		setSP(static_cast<uint16_t>(result));
	}

	void ArithmeticLogicUnit::INC(ArithmeticTargetRegister_unint16 reg)
	{
		uint16_t result = reg.get() + 1;
		reg.set(result);
	}

	void ArithmeticLogicUnit::DEC(ArithmeticTargetRegister_unint16 reg)
	{
		uint16_t result = reg.get() - 1;
		reg.set(result);
	}

	void ArithmeticLogicUnit::LD(int8_t value)
	{
		int16_t sp = static_cast<int16_t>(getSP());
		int16_t result = sp + value;
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag(((sp & 0x0F) + (value & 0x0F)) > 0x0F);
		setCarryFlag(((sp & 0xFF) + (value & 0xFF)) > 0xFF);
		setHL(static_cast<uint16_t>(result));
	}
#pragma endregion
}