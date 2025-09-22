#include "ControlUnit.h"
#include "MemoryBus.h"
#include "ArithmeticLogicUnit.h"
#include "Register.h"
#include "RegisterFile.h"

namespace CPU
{

	void ControlUnit::cycle()
	{
		// Check if CPU is halted or stopped
		if (stopped) {
			// In STOP mode, wait for button press
			uint8_t joypad = memory.read(0xFF00);
			if ((joypad & 0x0F) != 0x0F) {
				stopped = false;
			}
			else {
				// Still stopped, add idle cycles
				addCycles(4);
				return;
			}
		}
		
		if (halted) {
			// In HALT mode, check for interrupts
			uint8_t interruptFlag = memory.read(0xFF0F);
			uint8_t interruptEnable = memory.read(0xFFFF);
			
			if (interruptFlag & interruptEnable & 0x1F) {
				halted = false;
			}
			else {
				// Still halted, add idle cycles
				addCycles(4);
				return;
			}
		}
		
		// Process interrupts if enabled
		if (interruptsEnabled) {
			handleInterrupts();
		}
		
		// Fetch
		uint8_t opcode = fetch();
		step();
		
		// Decode/Execute
		decode(opcode);
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
		addCycles(4);
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
		addCycles(4);
		return result;
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
		addCycles(4);
	}

	void ControlUnit::ADC(uint8_t value)
	{
		uint8_t result = alu.ADC(registers.a.get(), value, registers.getCarryFlag());
		bool halfCarry = (registers.a.get() & 0x0F) + (value & 0x0F) + registers.getCarryFlag() > 0x0F;
		bool carry = result < registers.a.get() || (result == registers.a.get() && registers.getCarryFlag());
		setFlags(result, false, halfCarry, carry);
		registers.a.set(result);
		addCycles(4);
	}

	void ControlUnit::SBC(uint8_t value)
	{
		uint8_t result = alu.SBC(registers.a.get(), value, registers.getCarryFlag());
		bool halfCarry = (registers.a.get() & 0x0F) < (value & 0x0F) + registers.getCarryFlag();
		bool carry = result > registers.a.get() || (result == registers.a.get() && registers.getCarryFlag());
		setFlags(result, true, halfCarry, carry);
		registers.a.set(result);
		addCycles(4);
	}

	void ControlUnit::AND(uint8_t value)
	{
		uint8_t result = alu.AND(registers.a.get(), value);
		setFlags(result, false, true, false);
		registers.a.set(result);
		addCycles(4);
	}

	void ControlUnit::XOR(uint8_t value)
	{
		uint8_t result = alu.XOR(registers.a.get(), value);
		setFlags(result, false, false, false);
		registers.a.set(result);
		addCycles(4);
	}

	void ControlUnit::OR(uint8_t value)
	{
		uint8_t result = alu.OR(registers.a.get(), value);
		setFlags(result, false, false, false);
		registers.a.set(result);
		addCycles(4);
	}

	uint8_t ControlUnit::CP(uint8_t value)
	{
		uint8_t result = alu.SUB(registers.a.get(), value);
		setFlags(result, true, (registers.a.get() & 0x0F) < (value & 0x0F), result > registers.a.get());
		addCycles(4);
		return result;
	}

	void ControlUnit::CPL()
	{
		uint8_t result = alu.CPL(registers.a.get());
		setFlags(registers.getZeroFlag(), true, true, registers.getCarryFlag());
		registers.a.set(result);
		addCycles(4);
	}
#pragma endregion

#pragma region Rotates & Shifts

	void ControlUnit::RLCA()
	{
		uint8_t carry = registers.a.get() & 0x80;
		uint8_t result = alu.RLCA(registers.a.get());
		registers.a.set(result);
		setFlags(false, false, false, carry);
		addCycles(4);
	}

	void ControlUnit::RRCA()
	{
		uint8_t carry = registers.a.get() & 0x01;
		uint8_t result = alu.RRCA(registers.a.get());
		registers.a.set(result);
		setFlags(false, false, false, carry);
		addCycles(4);
	}

	void ControlUnit::RLA()
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RLA(registers.a.get(), carry);
		setFlags(false, false, false, carry & 0x80);
		registers.a.set(result);
		addCycles(4);
	}

	void ControlUnit::RRA()
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RRA(registers.a.get(), carry);
		setFlags(false, false, false, carry & 0x01);
		registers.a.set(result);
		addCycles(4);
	}

	uint8_t ControlUnit::RLC(uint8_t value)
	{
		uint8_t carry = value & 0x80;
		uint8_t result = alu.RLC(value);
		setFlags(result, false, false, carry);
		addCycles(8);
		return result;
	}

	uint8_t ControlUnit::RRC(uint8_t value)
	{
		uint8_t carry = value & 0x01;
		uint8_t result = alu.RRC(value);
		setFlags(result, false, false, carry);
		addCycles(8);
		return result;
	}

	uint8_t ControlUnit::RL(uint8_t value)
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RL(value, carry);
		setFlags(result, false, false, carry & 0x80);
		addCycles(8);
		return result;
	}

	uint8_t ControlUnit::RR(uint8_t value)
	{
		uint8_t carry = registers.getCarryFlag();
		uint8_t result = alu.RR(value, carry);
		setFlags(result, false, false, carry & 0x01);
		addCycles(8);
		return result;
	}

	uint8_t ControlUnit::SLA(uint8_t value)
	{
		uint8_t carry = value & 0x80;
		uint8_t result = alu.SLA(value);
		setFlags(result, false, false, carry);
		addCycles(8);
		return result;
	}

	uint8_t ControlUnit::SRA(uint8_t value)
	{
		uint8_t carry = value & 0x01;
		uint8_t result = alu.SRA(value);
		setFlags(result, false, false, carry);
		addCycles(8);
		return result;
	}

	uint8_t ControlUnit::SWAP(uint8_t value)
	{
		uint8_t result = alu.SWAP(value);
		setFlags(result, false, false, false);
		addCycles(8);
		return result;
	}

	uint8_t ControlUnit::SRL(uint8_t value)
	{
		uint8_t carry = value & 0x01;
		uint8_t result = alu.SRL(value);
		setFlags(result, false, false, carry);
		addCycles(8);
		return result;
	}
#pragma endregion

#pragma region Jump Instructions
	
	void ControlUnit::JR(bool flagCondition)
	{
		step();
		int8_t offset = static_cast<int8_t>(fetch());
		if (flagCondition) {
			registers.pc.set(registers.pc.get() + offset);
			addCycles(12);
		} else {
			addCycles(8);
		}
	}

	void ControlUnit::JP(bool flagCondition)
	{
		step();
		uint16_t address = memory.read16(registers.pc.get());
		if (flagCondition) {
			registers.pc.set(address);
			addCycles(16);
		} else {
			step();
			addCycles(12);
		}
	}
#pragma endregion

#pragma region Stack Instructions

	void ControlUnit::PUSH(uint16_t value)
	{
		registers.sp.set(registers.sp.get() - 0x0001);
		memory.write(registers.sp.get(), (value >> 8) & 0xFF);
		registers.sp.set(registers.sp.get() - 0x0001);
		memory.write(registers.sp.get(), value & 0xFF);
		addCycles(16);
	}

	void ControlUnit::POP(Register_uint16& reg)
	{
		uint8_t low = memory.read(registers.sp.get());
		registers.sp.set(registers.sp.get() + 0x0001);
		uint8_t high = memory.read(registers.sp.get());
		registers.sp.set(registers.sp.get() + 0x0001);
		reg.set((high << 8) | low);
		addCycles(12);
	}

	// Special handling for AF register pair
	void ControlUnit::PUSH_AF()
	{
		registers.sp.set(registers.sp.get() - 0x0001);
		memory.write(registers.sp.get(), registers.a.get());
		registers.sp.set(registers.sp.get() - 0x0001);
		memory.write(registers.sp.get(), registers.f.get());
		addCycles(16);
	}

	void ControlUnit::POP_AF()
	{
		uint8_t flags = memory.read(registers.sp.get()) & 0xF0; // Lower 4 bits always 0
		registers.sp.set(registers.sp.get() + 0x0001);
		uint8_t a = memory.read(registers.sp.get());
		registers.sp.set(registers.sp.get() + 0x0001);

		registers.a.set(a);
		registers.f.set(flags);
		addCycles(12);
	}
#pragma endregion

#pragma region Sub-Routines
	void ControlUnit::RET(bool flagCondition)
	{
		if (!flagCondition) {
			addCycles(8);
			return;
		}

		POP(registers.pc);
		addCycles(20); // 8 + 12 from POP
	}

	void ControlUnit::CALL(bool flagCondition)
	{
		step();
		uint16_t address = memory.read16(registers.pc.get());

		if (!flagCondition) {
			step();
			addCycles(12);
			return;
		}

		uint16_t returnAddress = registers.pc.get() + 0x0001;
		PUSH(returnAddress);
		registers.pc.set(address);
		addCycles(24); // 8 + 16 from PUSH
	}

	void ControlUnit::RST(uint8_t address)
	{
		uint16_t returnAddress = registers.pc.get();
		PUSH(returnAddress);
		registers.pc.set(address);
		addCycles(16); // Not counting PUSH cycles as they're added in PUSH
	}

	void ControlUnit::RETI()
	{
		RET();
		interruptsEnabled = true;
		addCycles(16);
	}

#pragma endregion

#pragma region Interupts and Clock
	void ControlUnit::handleInterrupts()
	{
		uint8_t interruptFlag = memory.read(0xFF0F);
		uint8_t interruptEnable = memory.read(0xFFFF);
		uint8_t pendingInterrupts = interruptFlag & interruptEnable & 0x1F;

		if (pendingInterrupts == 0)
			return;

		interruptsEnabled = false;
		PUSH(registers.pc.get());

		if (pendingInterrupts & 0x01) {  // V-Blank
			registers.pc.set(0x0040);
			memory.write(0xFF0F, interruptFlag & ~0x01);  // Clear interrupt flag
			addCycles(20);
		}
		else if (pendingInterrupts & 0x02) {  // LCD STAT
			registers.pc.set(0x0048);
			memory.write(0xFF0F, interruptFlag & ~0x02);
			addCycles(20);
		}
		else if (pendingInterrupts & 0x04) {  // Timer
			registers.pc.set(0x0050);
			memory.write(0xFF0F, interruptFlag & ~0x04);
			addCycles(20);
		}
		else if (pendingInterrupts & 0x08) {  // Serial
			registers.pc.set(0x0058);
			memory.write(0xFF0F, interruptFlag & ~0x08);
			addCycles(20);
		}
		else if (pendingInterrupts & 0x10) {  // Joypad
			registers.pc.set(0x0060);
			memory.write(0xFF0F, interruptFlag & ~0x10);
			addCycles(20);
		}
	
	void ControlUnit::EI()
	{
		interruptsEnabled = true;
		addCycles(4);
	}

	void ControlUnit::DI()
	{
		interruptsEnabled = false;
		addCycles(4);
	}

	void ControlUnit::HALT()
	{
		halted = true;
		addCycles(4);
	}

	void ControlUnit::STOP()
	{
		stopped = true;
		memory.write(0xFF04, 0);
		addCycles(4);
	}
#pragma endregion

	// Other Instructions
	void ControlUnit::BIT(uint8_t bit, uint8_t value)
	{
		uint8_t result = alu.BIT(bit, value);
		setFlags(result, false, true, registers.getCarryFlag());
		addCycles(8);
	}

	void ControlUnit::ADD(Register_uint16 reg)
	{
		uint16_t result = alu.ADD(registers.hl.get(), reg.get());
		bool halfCarry = (registers.hl.get() & 0x0FFF) + (registers.bc.get() & 0x0FFF) > 0x0FFF;
		setFlags(registers.getZeroFlag(), false, halfCarry, result < registers.hl.get());
		registers.hl.set(result);
		addCycles(8);
	}

	void ControlUnit::DAA()
	{
		uint8_t value = registers.a.get();
		bool carry = registers.getCarryFlag();

		if (registers.getSubtractionFlag())
		{
			if (registers.getHalfCarryFlag())
			{
				value -= 0x06;
			}

			if (carry)
			{
				value -= 0x60;
			}
		}
		else
		{
			if (registers.getHalfCarryFlag() || (value & 0x0F) > 0x09)
			{
				value += 0x06;
			}

			if (carry || value > 0x9F)
			{
				value += 0x60;
				carry = true;
			}
			else
			{
				carry = false;
			}
		}

		registers.a.set(value);
		registers.setZeroFlag(value == 0);
		registers.setHalfCarryFlag(false);
		registers.setCarryFlag(carry);
		addCycles(4);
	}
}