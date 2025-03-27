#include "ArithmeticLogicUnit.h"

namespace CPU {

	/*void ArithmeticLogicUnit::ADD(uint8_t value)
	{
		uint8_t result = getA() + value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag((getA() & 0x0F) + (value & 0x0F) > 0x0F);
		setCarryFlag(result < getA());
		setA(result);
	}*/

	/*void ArithmeticLogicUnit::ADC(uint8_t value)
	{
		uint8_t carry = getCarryFlag();
		uint8_t result = getA() + value + getCarryFlag();
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag((getA() & 0x0F) + (value & 0x0F) + getCarryFlag() > 0x0F);
		setCarryFlag(result < getA() || (result == getA() && carry));
		setA(result);
	}*/

	/*void ArithmeticLogicUnit::SUB(uint8_t value)
	{
		uint8_t result = getA() - value;
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (value & 0x0F));
		setCarryFlag(result > getA());
		setA(result);
	}*/

	/*void ArithmeticLogicUnit::SBC(uint8_t value)
	{
		uint8_t carry = getCarryFlag();
		uint8_t result = getA() - value - getCarryFlag();
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (value & 0x0F) + getCarryFlag());
		setCarryFlag(result > getA() || (result == getA() && carry));
		setA(result);
	}*/

	/*void ArithmeticLogicUnit::AND(uint8_t value)
	{
		uint8_t result = getA() & value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(true);
		setCarryFlag(false);
		setA(result);
	}*/

	/*void ArithmeticLogicUnit::OR(uint8_t value)
	{
		uint8_t result = getA() | value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}*/

	/*void ArithmeticLogicUnit::XOR(uint8_t value)
	{
		uint8_t result = getA() ^ value;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		setA(result);
	}*/

	/*void ArithmeticLogicUnit::CP(uint8_t value)
	{
		uint8_t result = getA() - value;
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((getA() & 0x0F) < (value & 0x0F));
		setCarryFlag(result > getA());
	}*/

	/*void ArithmeticLogicUnit::INC(Register_unint8 reg)
	{
		uint8_t result = reg.get() + 1;
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag((reg.get() & 0x0F) == 0x0F);
		reg.set(result);
	}*/

	/*void ArithmeticLogicUnit::DEC(Register_unint8 reg)
	{
		uint8_t result = reg.get() - 1;
		setZeroFlag(result == 0);
		setSubtractionFlag(true);
		setHalfCarryFlag((reg.get() & 0x0F) == 0x00);
		reg.set(result);
	}*/

	/*void ArithmeticLogicUnit::CPL()
	{
		setA(getA() ^ 0xFF);
		setSubtractionFlag(true);
		setHalfCarryFlag(true);
	}*/

	/*void ArithmeticLogicUnit::ADD(ArithmeticTargetRegister_unint16 reg)
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
	}*/

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


	/*void ArithmeticLogicUnit::CCF()
	{
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(!getCarryFlag());
	}

	void ArithmeticLogicUnit::SCF()
	{
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(true);
	}*/

	/*void ArithmeticLogicUnit::RRA()
	{
		uint8_t carry = getCarryFlag();
		setCarryFlag(getA() & 0x01);
		setA((getA() >> 1) | (carry << 7));
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}

	void ArithmeticLogicUnit::RLA()
	{
		uint8_t carry = getCarryFlag();
		setCarryFlag(getA() & 0x80);
		setA((getA() << 1) | carry);
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}*/

	/*void ArithmeticLogicUnit::RRCA()
	{
		setCarryFlag(getA() & 0x01);
		setA((getA() >> 1) | (getA() << 7));
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}

	void ArithmeticLogicUnit::RLCA()
	{
		setCarryFlag(getA() & 0x80);
		setA((getA() << 1) | (getA() >> 7));
		setZeroFlag(false);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}*/

	/*void ArithmeticLogicUnit::SRL(ArithmeticTargetRegister_unint8 reg)
	{
		setCarryFlag(reg.get() & 0x01);
		reg.set(reg.get() >> 1);
		setZeroFlag(reg.get() == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}*/

	//void ArithmeticLogicUnit::RR(ArithmeticTargetRegister_unint8 reg)
	//{
	//	uint8_t carry = getCarryFlag();
	//	setCarryFlag(reg.get() & 0x01);
	//	reg.set((reg.get() >> 1) | (carry << 7));
	//	setZeroFlag(reg.get() == 0);
	//	setSubtractionFlag(false);
	//	setHalfCarryFlag(false);
	//}

	/*void ArithmeticLogicUnit::RL(ArithmeticTargetRegister_unint8 reg)
	{
		uint8_t carry = getCarryFlag();
		setCarryFlag(reg.get() & 0x80);
		reg.set((reg.get() << 1) | carry);
		setZeroFlag(reg.get() == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}

	void ArithmeticLogicUnit::RRC(ArithmeticTargetRegister_unint8 reg)
	{
		setCarryFlag(reg.get() & 0x01);
		reg.set((reg.get() >> 1) | (reg.get() << 7));
		setZeroFlag(reg.get() == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}*/

	/*void ArithmeticLogicUnit::RLC(ArithmeticTargetRegister_unint8 reg)
	{
		setCarryFlag(reg.get() & 0x80);
		reg.set((reg.get() << 1) | (reg.get() >> 7));
		setZeroFlag(reg.get() == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}*/

	/*void ArithmeticLogicUnit::SRA(ArithmeticTargetRegister_unint8 reg)
	{
		setCarryFlag(reg.get() & 0x01);
		reg.set((reg.get() >> 1) | (reg.get() & 0x80));
		setZeroFlag(reg.get() == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}*/

	/*void ArithmeticLogicUnit::SLA(ArithmeticTargetRegister_unint8 reg)
	{
		setCarryFlag(reg.get() & 0x80);
		reg.set(reg.get() << 1);
		setZeroFlag(reg.get() == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
	}*/

	/*void ArithmeticLogicUnit::SWAP(ArithmeticTargetRegister_unint8 reg)
	{
		uint8_t result = ((reg.get() & 0x0F) << 4) | ((reg.get() & 0xF0) >> 4);
		setZeroFlag(result == 0);
		setSubtractionFlag(false);
		setHalfCarryFlag(false);
		setCarryFlag(false);
		reg.set(result);
	}*/

	/*void ArithmeticLogicUnit::BIT(uint8_t bit, uint8_t& address) {
		setZeroFlag(!(address & (1 << bit)));
		setSubtractionFlag(false);
		setHalfCarryFlag(true);
	}*/

	/*void ArithmeticLogicUnit::BIT(uint8_t bit, ArithmeticTargetRegister_unint8 reg)
	{
		setZeroFlag(!(reg.get() & (1 << bit)));
		setSubtractionFlag(false);
		setHalfCarryFlag(true);
	}*/

	//void ArithmeticLogicUnit::SET(uint8_t bit, uint8_t& address) { address |= (1 << bit); }
	//void ArithmeticLogicUnit::SET(uint8_t bit, ArithmeticTargetRegister_unint8 reg) { reg.set(reg.get() | (1 << bit)); }

	//void ArithmeticLogicUnit::RES(uint8_t bit, uint8_t& address) { address &= ~(1 << bit); }
	//void ArithmeticLogicUnit::RES(uint8_t bit, ArithmeticTargetRegister_unint8 reg) { reg.set(reg.get() & ~(1 << bit)); }
}