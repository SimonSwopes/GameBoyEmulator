#pragma once
#include "Register.h"
namespace CPU {

	class ArithmeticLogicUnit
	{

		public:
			ArithmeticLogicUnit(){}

			// 8 bit arithmetic
			uint8_t ADD(uint8_t num1, uint8_t num2) { return num1 + num2; }
			uint8_t ADC(uint8_t num1, uint8_t num2, uint8_t carry) { return num1 + num2 + carry; }
			uint8_t SUB(uint8_t num1, uint8_t num2) { return num1 - num2; }
			uint8_t SBC(uint8_t num1, uint8_t num2, uint8_t carry) { return num1 - num2 - carry; }

			// 8 bit logical
			uint8_t AND(uint8_t num1, uint8_t num2) { return num1 & num2; }
			uint8_t OR(uint8_t num1, uint8_t num2) { return num1 | num2; }
			uint8_t XOR(uint8_t num1, uint8_t num2) { return num1 ^ num2; }

			// 8 Bit INC/DEC
			uint8_t INC(uint8_t num) { return num + 1; }
			uint8_t DEC(uint8_t num) { return num - 1; }
			uint8_t CPL(uint8_t num) { return XOR(num, 0xFF); }

			// 16 bit arithmetic
			uint16_t ADD(uint16_t num1, uint16_t num2) { return num1 + num2; }
			void INC(Register_uint16 reg);
			void DEC(Register_uint16 reg);

			// Rotates and Shifts
			uint8_t RRA(uint8_t value, uint8_t carry) { return (value >> 1) | (carry << 7); }
			uint8_t RLA(uint8_t value, uint8_t carry) { return (value << 1) | carry; }
			uint8_t RRCA(uint8_t value) { return (value >> 1) | (value << 7); }
			uint8_t RLCA(uint8_t value) { return (value << 1) | (value >> 7); }
			uint8_t SRL(uint8_t value) { return value >> 1; }
			uint8_t RR(uint8_t value, uint8_t carry) { return (value >> 1) | (carry << 7); }
			uint8_t RL(uint8_t value, uint8_t carry) { return (value << 1) | carry; }
			uint8_t RRC(uint8_t value) { return (value >> 1) | (value << 7); }
			uint8_t RLC(uint8_t value) { return (value << 1) | (value >> 7); }
			uint8_t SRA(uint8_t value) { return ((value >> 1) | (value & 0x80)); }
			uint8_t SLA(uint8_t value) { return value << 1; }
			uint8_t SWAP(uint8_t value) { return ((value & 0x0F) << 4) | ((value & 0xF0) >> 4); }

			// Single Bit Operations
			uint8_t BIT(uint8_t bit, uint8_t value) { return value & (1 << bit); }
			uint8_t SET(uint8_t bit, uint8_t value) { return value | (1 << bit); }
			uint8_t RES(uint8_t bit, uint8_t value) { return value & ~(1 << bit); }
	};
}