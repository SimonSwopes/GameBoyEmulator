#include "ControlUnit.h"
#include "MemoryBus.h"
#include "ArithmeticLogicUnit.h"
#include "Register.h"
#include "RegisterFile.h"

namespace CPU
{

	void ControlUnit::cycle()
	{
		// Fetch
		uint8_t opcode = fetch();

		// Decode/Execute
		decode(opcode);

		// Increment PC
		step();
	}


	void ControlUnit::setFlags(bool zero, bool sub, bool half, bool carry)
	{
		registers.setZeroFlag(zero);
		registers.setSubtractionFlag(sub);
		registers.setHalfCarryFlag(half);
		registers.setCarryFlag(carry);
	}

#pragma region 8Bit Arithmetic
	uint8_t ControlUnit::INC(uint8_t value)
	{
		uint8_t result = alu.INC(value);
		setFlags(result, false, (value & 0x0F) == 0x0F, registers.getCarryFlag());
		return result;
	}

	void ControlUnit::INC(Register_unint8 reg)
	{
		uint8_t result = INC(reg.get());
		reg.set(result);
	}

	uint8_t ControlUnit::DEC(uint8_t value)
	{
		uint8_t result = alu.DEC(value);
		setFlags(result, true, (value & 0x0F) == 0x00, registers.getCarryFlag());
	}

	void ControlUnit::DEC(Register_unint8 reg)
	{
		uint8_t result = DEC(reg.get());
		reg.set(result);
	}

	void ControlUnit::ADD(uint8_t value)
	{
		uint8_t result = alu.ADD(registers.a.get(), value);
		setFlags(result, false, (registers.a.get() & 0x0F) + (value & 0x0F) > 0x0F, result < registers.a.get());
		registers.a.set(result);
	}

	void ControlUnit::ADC(uint8_t value)
	{
		uint8_t result = alu.ADC(registers.a.get(), value, registers.getCarryFlag());
		bool halfCarry = (registers.a.get() & 0x0F) + (value & 0x0F) + registers.getCarryFlag() > 0x0F;
		bool carry = result < registers.a.get() || (result == registers.a.get() && registers.getCarryFlag());
		setFlags(result, false, halfCarry, carry);
		registers.a.set(result);
	}

	void ControlUnit::SBC(uint8_t value)
	{
		uint8_t result = alu.SBC(registers.a.get(), value, registers.getCarryFlag());
		bool halfCarry = (registers.a.get() & 0x0F) < (value & 0x0F) + registers.getCarryFlag();
		bool carry = result > registers.a.get() || (result == registers.a.get() && registers.getCarryFlag());
		setFlags(result, true, halfCarry, carry);
		registers.a.set(result);
	}

	void ControlUnit::AND(uint8_t value)
	{
		uint8_t result = alu.AND(registers.a.get(), value);
		setFlags(result, false, true, false);
		registers.a.set(result);
	}

	void ControlUnit::XOR(uint8_t value)
	{
		uint8_t result = alu.XOR(registers.a.get(), value);
		setFlags(result, false, false, false);
		registers.a.set(result);
	}

	void ControlUnit::OR(uint8_t value)
	{
		uint8_t result = alu.OR(registers.a.get(), value);
		setFlags(result, false, false, false);
		registers.a.set(result);
	}

	uint8_t ControlUnit::CP(uint8_t value)
	{
		uint8_t result = alu.SUB(registers.a.get(), value);
		setFlags(result, true, (registers.a.get() & 0x0F) < (value & 0x0F), result > registers.a.get());
		return result;
	}

	void ControlUnit::CPL()
	{
		uint8_t result = alu.CPL(registers.a.get());
		setFlags(registers.getZeroFlag(), true, true, registers.getCarryFlag());
		registers.a.set(result);
	}
#pragma endregion


#pragma region Rotates & Shifts

	void ControlUnit::RLCA()
	{
		uint8_t carry = registers.a.get() & 0x80;
		uint8_t result = alu.RLCA(registers.a.get());
		registers.a.set(result);
		setFlags(false, false, false, carry);
	}

	void ControlUnit::RRCA()
	{
		uint8_t carry = registers.a.get() & 0x01;
		uint8_t result = alu.RRCA(registers.a.get());
		registers.a.set(result);
		setFlags(false, false, false, carry);
	}

	void ControlUnit::RLA()
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RLA(registers.a.get(), carry);
		setFlags(false, false, false, carry & 0x80);
		registers.a.set(result);
	}

	void ControlUnit::RRA()
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RRA(registers.a.get(), carry);
		setFlags(false, false, false, carry & 0x01);
		registers.a.set(result);
	}

	uint8_t ControlUnit::RLC(uint8_t value)
	{
		uint8_t carry = value & 0x80;
		uint8_t result = alu.RLC(value);
		setFlags(result, false, false, carry);
		return result;
	}

	uint8_t ControlUnit::RRC(uint8_t value)
	{
		uint8_t carry = value & 0x01;
		uint8_t result = alu.RRC(value);
		setFlags(result, false, false, carry);
		return result;
	}

	uint8_t ControlUnit::RL(uint8_t value)
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RL(value, carry);
		setFlags(result, false, false, carry & 0x80);
		return result;
	}

	uint8_t ControlUnit::RR(uint8_t value)
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RR(value, carry);
		setFlags(result, false, false, carry & 0x01);
		return result;
	}

	uint8_t ControlUnit::SLA(uint8_t value)
	{
		uint8_t carry = value & 0x80;
		uint8_t result = alu.SLA(value);
		setFlags(result, false, false, carry);
		return result;
	}

	uint8_t ControlUnit::SRA(uint8_t value)
	{
		uint8_t carry = value & 0x01;
		uint8_t result = alu.SRA(value);
		setFlags(result, false, false, carry);
		return result;
	}

	uint8_t ControlUnit::SWAP(uint8_t value)
	{
		uint8_t result = alu.SWAP(value);
		setFlags(result, false, false, false);
		return result;
	}

	uint8_t ControlUnit::SRL(uint8_t value)
	{
		uint8_t carry = value & 0x01;
		uint8_t result = alu.SRL(value);
		setFlags(result, false, false, carry);
		return result;
	}
#pragma endregion

	// Bit Operations
	void ControlUnit::BIT(uint8_t bit, uint8_t value)
	{
		uint8_t result = alu.BIT(bit, value);
		setFlags(result, false, true, registers.getCarryFlag());
	}

	// 16 Bit Arithmetic
	void ControlUnit::ADD(Register_uint16 reg)
	{
		uint16_t result = alu.ADD(registers.hl.get(), reg.get());
		bool halfCarry = (registers.hl.get() & 0x0FFF) + (registers.bc.get() & 0x0FFF) > 0x0FFF;
		setFlags(registers.getZeroFlag(), false, halfCarry , result < registers.hl.get());
		registers.hl.set(result);
	}
}