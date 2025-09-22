#pragma once
#include <cstdint>;
#include "Register.h"
namespace CPU
{
	class ControlUnit
	{
		public:
			ControlUnit() : alu(), memory(), registers() {}

		private:
			RegisterFile registers;
			ArithmeticLogicUnit alu;
			Ram::MemoryBus memory;

			void cycle(); // This may need to be public and hit by main
			void decode(uint8_t opcode);
			void decodeCBIns();
			uint8_t fetch() { return memory.read(registers.pc.get()); }
			void step() { registers.pc.set(registers.pc.get() + 1); }

			void setFlags(bool zero, bool sub, bool half, bool carry);
			void setFlags(uint8_t result, bool sub, bool half, bool carry) { setFlags(result == 0, sub, half, carry); }

			// Instruction Methods

#pragma region 8Bit Arithmetic
			uint8_t INC(uint8_t value);
			void INC(Register_unint8 reg);
			void INC(Register_uint16 reg) { alu.INC(reg); }
			uint8_t DEC(uint8_t value);
			void DEC(Register_unint8 reg);
			void DEC(Register_uint16 reg) { alu.DEC(reg); }

			void ADD(uint8_t value);
			void ADD(Register_unint8 reg) { ADD(reg.get()); }

			void ADC(uint8_t value);
			void ADC(Register_unint8 reg) { ADC(reg.get()); }

			void SUB(uint8_t value) { registers.a.set(CP(value)); }
			void SUB(Register_unint8 reg) { SUB(reg.get()); }

			void SBC(uint8_t value);
			void SBC(Register_unint8 reg) { SBC(reg.get()); }

			void AND(uint8_t value);
			void AND(Register_unint8 reg) { AND(reg.get()); }

			void XOR(uint8_t value);
			void XOR(Register_unint8 reg) { XOR(reg.get()); }

			void OR(uint8_t value);
			void OR(Register_unint8 reg) { OR(reg.get()); }

			uint8_t CP(uint8_t value);
			uint8_t CP(Register_unint8 reg) { return CP(reg.get()); }
			void CPL();
#pragma endregion


#pragma region Rotates & Shifts
			void RLCA();
			void RRCA();
			void RLA();
			void RRA();

			uint8_t RLC(uint8_t value);
			void RLC(Register_unint8 reg) { reg.set(RLC(reg.get())); }

			uint8_t RRC(uint8_t value);
			void RRC(Register_unint8 reg) { reg.set(RRC(reg.get())); }

			uint8_t RL(uint8_t value);
			void RL(Register_unint8 reg) { reg.set(RL(reg.get())); }

			uint8_t RR(uint8_t value);
			void RR(Register_unint8 reg) { reg.set(RR(reg.get())); }

			uint8_t SLA(uint8_t value);
			void SLA(Register_unint8 reg) { reg.set(SLA(reg.get())); }

			uint8_t SRA(uint8_t value);
			void SRA(Register_unint8 reg) { reg.set(SRA(reg.get())); }

			uint8_t SWAP(uint8_t value);
			void SWAP(Register_unint8 reg) { reg.set(SWAP(reg.get())); }

			uint8_t SRL(uint8_t value);
			void SRL(Register_unint8 reg) { reg.set(SRL(reg.get())); }

#pragma endregion

			
#pragma region Bit Operations
			void BIT(uint8_t bit, uint8_t value);
			void BIT(uint8_t bit, Register_unint8 reg) { BIT(bit, reg.get()); }

			uint8_t SET(uint8_t bit, uint8_t value) { return alu.SET(bit, value); }
			void SET(uint8_t bit, Register_unint8 reg) { reg.set(SET(bit, reg.get())); }

			uint8_t RES(uint8_t bit, uint8_t value) { return alu.RES(bit, value); }
			void RES(uint8_t bit, Register_unint8 reg) { reg.set(RES(bit, reg.get())); }
#pragma endregion

#pragma region Jump Instructions
			void JR(bool flagCondition = true);
			void JP(bool flagCondition = true);
#pragma endregion

#pragma region Stack Instructions
			uint16_t POP();
			void PUSH(Register_uint16& reg);
			void POP(Register_uint16& reg);

			// Requires special handling since F register lower 4 bits are always 0
			void PUSH_AF();
			void POP_AF();
#pragma endregion

#pragma region Sub-Routines
			void RET(bool flagCondition = true);
#pragma endregion


			// 16 Bit Arithmetic
			void ADD(Register_uint16 reg);

			// Loads
			void LD(Register_unint8 reg, uint8_t value) { reg.set(value); }
			void LD(Register_unint8 reg1, Register_unint8 reg2) { LD(reg1, reg2.get()); }
			void LD(Register_uint16 reg, uint16_t value) { reg.set(value); }
			void LD(Register_uint16 reg1, Register_uint16 reg2) { LD(reg1, reg2.get()); }

			// Others
			void DAA();
			void SCF() { registers.setCarryFlag(true); registers.setHalfCarryFlag(false); registers.setSubtractionFlag(false); }
			void CCF() { registers.setCarryFlag(!registers.getCarryFlag()); registers.setHalfCarryFlag(false); registers.setSubtractionFlag(false); }
	};
}