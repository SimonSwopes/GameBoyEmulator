#include "ControlUnit.h"
#include "MemoryBus.h"
#include "ArithmeticLogicUnit.h"
#include "Register.h"

namespace CPU
{

	// TODO: Pretty much anything with mem access or immediate values
	void ControlUnit::step()
	{
		// Fetch
		uint8_t opcode = memory.read(pc.get());

		// Decode/Execute
		decode(opcode);

		// Increment PC
		pc.set(pc.get() + 1);
	}

	// If this becomes hard to maintain consider breaking up nibble
	// Special thanks to https://gbdev.io/gb-opcodes/optables/
	void ControlUnit::decode(uint8_t opcode)
	{
		if (opcode == 0xCB)
		{
			pc.set(pc.get() + 1);
			decodeCBIns();
			return;
		}

		switch (opcode)
		{
			// 0x00 - 0x0F
			case 0x00: // NOP
				break;
			case 0x01: // LD BC, d16
				break;
			case 0x02: // LD (BC), A
				break;
			case 0x03: // INC BC
				alu.INC(alu.bc);
				break;
			case 0x04: // INC B
				alu.INC(alu.b);
				break;
			case 0x05: // DEC B
				alu.DEC(alu.b);
				break;
			case 0x06: // LD B, d8
				break;
			case 0x07: // RLCA
				alu.RLCA();
				break;
			case 0x08: // LD (a16), SP
				break;
			case 0x09: // ADD HL, BC
				alu.ADD(alu.bc);
				break;
			case 0x0A: // LD A, (BC)
				break;
			case 0x0B: // DEC BC
				alu.DEC(alu.bc);
				break;
			case 0x0C: // INC C
				alu.INC(alu.c);
				break;
			case 0x0D: // DEC C
				alu.DEC(alu.c);
				break;
			case 0x0E: // LD C, d8
				break;
			case 0x0F: // RRCA
				alu.RRCA();
				break;
			
			// 0x10 - 0x1F
			case 0x10: // STOP 0
				break;
			case 0x11: // LD DE, d16
				break;
			case 0x12: // LD (DE), A
				break;
			case 0x13: // INC DE
				alu.INC(alu.de);
				break;
			case 0x14: // INC D
				alu.INC(alu.d);
				break;
			case 0x15: // DEC D
				alu.DEC(alu.d);
				break;
			case 0x16: // LD D, d8
				break;
			case 0x17: // RLA
				alu.RLA();
				break;
			case 0x18: // JR r8
				break;
			case 0x19: // ADD HL, DE
				alu.ADD(alu.de);
				break;
			case 0x1A: // LD A, (DE)
				break;
			case 0x1B: // DEC DE
				alu.DEC(alu.de);
				break;
			case 0x1C: // INC E
				alu.INC(alu.e);
				break;
			case 0x1D: // DEC E
				alu.DEC(alu.e);
				break;
			case 0x1E: // LD E, d8
				break;
			case 0x1F: // RRA
				alu.RRA();
				break;

			// 0x20 - 0x2F
			case 0x20: // JR NZ, r8
				break;
			case 0x21: // LD HL, d16
				break;
			case 0x22: // LD (HL+), A
				break;
			case 0x23: // INC HL
				alu.INC(alu.hl);
				break;
			case 0x24: // INC H
				alu.INC(alu.h);
				break;
			case 0x25: // DEC H
				alu.DEC(alu.h);
				break;
			case 0x26: // LD H, d8
				break;
			case 0x27: // DAA
				break;
			case 0x28: // JR Z, r8
				break;
			case 0x29: // ADD HL, HL
				alu.ADD(alu.hl);
				break;
			case 0x2A: // LD A, (HL+)
				break;
			case 0x2B: // DEC HL
				alu.DEC(alu.hl);
				break;
			case 0x2C: // INC L
				alu.INC(alu.l);
				break;
			case 0x2D: // DEC L
				alu.DEC(alu.l);
				break;
			case 0x2E: // LD L, d8
				break;
			case 0x2F: // CPL
				alu.CPL();
				break;
			
			// 0x30 - 0x3F
			case 0x30: // JR NC, r8
				break;
			case 0x31: // LD SP, d16
				break;
			case 0x32: // LD (HL-), A
				break;
			case 0x33: // INC SP
				alu.INC(alu.sp);
				break;
			case 0x34: // INC (HL)
				alu.INC(alu.hl);
				break;
			case 0x35: // DEC (HL)
				alu.DEC(alu.hl);
				break;
			case 0x36: // LD (HL), d8
				break;
			case 0x37: // SCF
				alu.SCF();
				break;
			case 0x38: // JR C, r8
				break;
			case 0x39: // ADD HL, SP
				alu.ADD(alu.sp);
				break;
			case 0x3A: // LD A, (HL-)
				break;
			case 0x3B: // DEC SP
				alu.DEC(alu.sp);
				break;
			case 0x3C: // INC A
				alu.INC(alu.a);
				break;
			case 0x3D: // DEC A
				alu.DEC(alu.a);
				break;
			case 0x3E: // LD A, d8
				break;
			case 0x3F: // CCF
				alu.CCF();
				break;

			case 0x40: // LD B, B
				break;
			case 0x41: // LD B, C
				break;
			case 0x42: // LD B, D
				break;
			case 0x43: // LD B, E
				break;
			case 0x44: // LD B, H
				break;
			case 0x45: // LD B, L
				break;
			case 0x46: // LD B, (HL)
				break;
			case 0x47: // LD B, A
				break;
			case 0x48: // LD C, B
				break;
			case 0x49: // LD C, C
				break;
			case 0x4A: // LD C, D
				break;
			case 0x4B: // LD C, E
				break;
			case 0x4C: // LD C, H
				break;
			case 0x4D: // LD C, L
				break;
			case 0x4E: // LD C, (HL)
				break;
			case 0x4F: // LD C, A
				break;
			
			// 0x50 - 0x5F
			case 0x50: // LD D, B
				break;
			case 0x51: // LD D, C
				break;
			case 0x52: // LD D, D
				break;
			case 0x53: // LD D, E
				break;
			case 0x54: // LD D, H
				break;
			case 0x55: // LD D, L
				break;
			case 0x56: // LD D, (HL)
				break;
			case 0x57: // LD D, A
				break;
			case 0x58: // LD E, B
				break;
			case 0x59: // LD E, C
				break;
			case 0x5A: // LD E, D
				break;
			case 0x5B: // LD E, E
				break;
			case 0x5C: // LD E, H
				break;
			case 0x5D: // LD E, L
				break;
			case 0x5E: // LD E, (HL)
				break;
			case 0x5F: // LD E, A
				break;

			// 0x60 - 0x6F
			case 0x60: // LD H, B
				break;
			case 0x61: // LD H, C
				break;
			case 0x62: // LD H, D
				break;
			case 0x63: // LD H, E
				break;
			case 0x64: // LD H, H
				break;
			case 0x65: // LD H, L
				break;
			case 0x66: // LD H, (HL)
				break;
			case 0x67: // LD H, A
				break;
			case 0x68: // LD L, B
				break;
			case 0x69: // LD L, C
				break;
			case 0x6A: // LD L, D
				break;
			case 0x6B: // LD L, E
				break;
			case 0x6C: // LD L, H
				break;
			case 0x6D: // LD L, L
				break;
			case 0x6E: // LD L, (HL)
				break;
			case 0x6F: // LD L, A
				break;

			// 0x70 - 0x7F
			case 0x70: // LD (HL), B
				break;
			case 0x71: // LD (HL), C
				break;
			case 0x72: // LD (HL), D
				break;
			case 0x73: // LD (HL), E
				break;
			case 0x74: // LD (HL), H
				break;
			case 0x75: // LD (HL), L
				break;
			case 0x76: // HALT
				break;
			case 0x77: // LD (HL), A
				break;
			case 0x78: // LD A, B
				break;
			case 0x79: // LD A, C
				break;
			case 0x7A: // LD A, D
				break;
			case 0x7B: // LD A, E
				break;
			case 0x7C: // LD A, H
				break;
			case 0x7D: // LD A, L
				break;
			case 0x7E: // LD A, (HL)
				break;
			case 0x7F: // LD A, A
				break;
			
			// 0x80 - 0x8F
			case 0x80: // ADD A, B
				alu.ADD(alu.b);
				break;
			case 0x81: // ADD A, C
				alu.ADD(alu.c);
				break;
			case 0x82: // ADD A, D
				alu.ADD(alu.d);
				break;
			case 0x83: // ADD A, E
				alu.ADD(alu.e);
				break;
			case 0x84: // ADD A, H
				alu.ADD(alu.h);
				break;
			case 0x85: // ADD A, L
				alu.ADD(alu.l);
				break;
			case 0x86: // ADD A, (HL)
				break;
			case 0x87: // ADD A, A
				alu.ADD(alu.a);
				break;
			case 0x88: // ADC A, B
				alu.ADC(alu.b);
				break;
			case 0x89: // ADC A, C
				alu.ADC(alu.c);
				break;
			case 0x8A: // ADC A, D
				alu.ADC(alu.d);
				break;
			case 0x8B: // ADC A, E
				alu.ADC(alu.e);
				break;
			case 0x8C: // ADC A, H
				alu.ADC(alu.h);
				break;
			case 0x8D: // ADC A, L
				alu.ADC(alu.l);
				break;
			case 0x8E: // ADC A, (HL)
				break;
			case 0x8F: // ADC A, A
				alu.ADC(alu.a);
				break;

			// 0x90 - 0x9F
			case 0x90: // SUB A, B
				alu.SUB(alu.b);
				break;
			case 0x91: // SUB A, C
				alu.SUB(alu.c);
				break;
			case 0x92: // SUB A, D
				alu.SUB(alu.d);
				break;
			case 0x93: // SUB A, E
				alu.SUB(alu.e);
				break;
			case 0x94: // SUB A, H
				alu.SUB(alu.h);
				break;
			case 0x95: // SUB A, L
				alu.SUB(alu.l);
				break;
			case 0x96: // SUB A, (HL)
				break;
			case 0x97: // SUB A, A
				alu.SUB(alu.a);
				break;
			case 0x98: // SBC A, B
				alu.SBC(alu.b);
				break;
			case 0x99: // SBC A, C
				alu.SBC(alu.c);
				break;
			case 0x9A: // SBC A, D
				alu.SBC(alu.d);
				break;
			case 0x9B: // SBC A, E
				alu.SBC(alu.e);
				break;
			case 0x9C: // SBC A, H
				alu.SBC(alu.h);
				break;
			case 0x9D: // SBC A, L
				alu.SBC(alu.l);
				break;
			case 0x9E: // SBC A, (HL)
				break;
			case 0x9F: // SBC A, A
				alu.SBC(alu.a);
				break;

			// 0xA0 - 0xAF
			case 0xA0: // AND A, B
				alu.AND(alu.b);
				break;
			case 0xA1: // AND A, C
				alu.AND(alu.c);
				break;
			case 0xA2: // AND A, D
				alu.AND(alu.d);
				break;
			case 0xA3: // AND A, E
				alu.AND(alu.e);
				break;
			case 0xA4: // AND A, H
				alu.AND(alu.h);
				break;
			case 0xA5: // AND A, L
				alu.AND(alu.l);
				break;
			case 0xA6: // AND A, (HL)
				break;
			case 0xA7: // AND A, A
				alu.AND(alu.a);
				break;
			case 0xA8: // XOR A, B
				alu.XOR(alu.b);
				break;
			case 0xA9: // XOR A, C
				alu.XOR(alu.c);
				break;
			case 0xAA: // XOR A, D
				alu.XOR(alu.d);
				break;
			case 0xAB: // XOR A, E
				alu.XOR(alu.e);
				break;
			case 0xAC: // XOR A, H
				alu.XOR(alu.h);
				break;
			case 0xAD: // XOR A, L
				alu.XOR(alu.l);
				break;
			case 0xAE: // XOR A, (HL)
				break;
			case 0xAF: // XOR A, A
				alu.XOR(alu.a);
				break;

			// 0xB0 - 0xBF
			case 0xB0: // OR A, B
				alu.OR(alu.b);
				break;
			case 0xB1: // OR A, C
				alu.OR(alu.c);
				break;
			case 0xB2: // OR A, D
				alu.OR(alu.d);
				break;
			case 0xB3: // OR A, E
				alu.OR(alu.e);
				break;
			case 0xB4: // OR A, H
				alu.OR(alu.h);
				break;
			case 0xB5: // OR A, L
				alu.OR(alu.l);
				break;
			case 0xB6: // OR A, (HL)
				break;
			case 0xB7: // OR A, A
				alu.OR(alu.a);
				break;
			case 0xB8: // CP A, B
				alu.CP(alu.b);
				break;
			case 0xB9: // CP A, C
				alu.CP(alu.c);
				break;
			case 0xBA: // CP A, D
				alu.CP(alu.d);
				break;
			case 0xBB: // CP A, E
				alu.CP(alu.e);
				break;
			case 0xBC: // CP A, H
				alu.CP(alu.h);
				break;
			case 0xBD: // CP A, L
				alu.CP(alu.l);
				break;
			case 0xBE: // CP A, (HL)
				break;
			case 0xBF: // CP A, A
				alu.CP(alu.a);
				break;

			// 0xC0 - 0xCF
			case 0xC0: // RET NZ
				break;
			case 0xC1: // POP BC
				break;
			case 0xC2: // JP NZ, a16
				break;
			case 0xC3: // JP a16
				break;
			case 0xC4: // CALL NZ, a16
				break;
			case 0xC5: // PUSH BC
				break;
			case 0xC6: // ADD A, d8
				break;
			case 0xC7: // RST 00H
				break;
			case 0xC8: // RET Z
				break;
			case 0xC9: // RET
				break;
			case 0xCA: // JP Z, a16
				break;
			case 0xCC: // CALL Z, a16
				break;
			case 0xCD: // CALL a16
				break;
			case 0xCE: // ADC A, d8
				break;
			case 0xCF: // RST 08H
				break;
			
			// 0xD0 - 0xDF
			case 0xD0: // RET NC
				break;
			case 0xD1: // POP DE
				break;
			case 0xD2: // JP NC, a16
				break;
			case 0xD4: // CALL NC, a16
				break;
			case 0xD5: // PUSH DE
				break;
			case 0xD6: // SUB A, d8
				break;
			case 0xD7: // RST 10H
				break;
			case 0xD8: // RET C
				break;
			case 0xD9: // RETI
				break;
			case 0xDA: // JP C, a16
				break;
			case 0xDC: // CALL C, a16
				break;
			case 0xDE: // SBC A, d8
				break;
			case 0xDF: // RST 18H
				break;

			// 0xE0 - 0xEF
			case 0xE0: // LDH (a8), A
				break;
			case 0xE1: // POP HL
				break;
			case 0xE2: // LD (C), A
				break;
			case 0xE5: // PUSH HL
				break;
			case 0xE6: // AND A, d8
				break;
			case 0xE7: // RST 20H
				break;
			case 0xE8: // ADD SP, r8
				break;
			case 0xE9: // JP HL
				break;
			case 0xEA: // LD (a16), A
				break;
			case 0xEE: // XOR A, d8
				break;
			case 0xEF: // RST 28H
				break;

			case 0xF0: // LDH A, (a8)
				break;
			case 0xF1: // POP AF
				break;
			case 0xF2: // LD A, (C)
				break;
			case 0xF3: // DI
				break;
			case 0xF5: // PUSH AF
				break;
			case 0xF6: // OR A, d8
				break;
			case 0xF7: // RST 30H
				break;
			case 0xF8: // LD HL, SP+r8
				break;
			case 0xF9: // LD SP, HL
				break;
			case 0xFA: // LD A, (a16)
				break;
			case 0xFB: // EI
				break;
			case 0xFE: // CP A, d8
				break;
			case 0xFF: // RST 38H
				break;

			default: // TODO: Log Error Data Here
				break;

		}

	}

	void ControlUnit::decodeCBIns()
	{
		// Instruction data next byte
		uint8_t opcode = memory.read(pc.get());

		switch (opcode)
		{
			// 0x00 - 0x0F
			case 0x00: // RLC B
				alu.RLC(alu.b);
				break;
			case 0x01: // RLC C
				alu.RLC(alu.c);
				break;
			case 0x02: // RLC D
				alu.RLC(alu.d);
				break;
			case 0x03: // RLC E
				alu.RLC(alu.e);
				break;
			case 0x04: // RLC H
				alu.RLC(alu.h);
				break;
			case 0x05: // RLC L
				alu.RLC(alu.l);
				break;
			case 0x06: // RLC (HL)
				break;
			case 0x07: // RLC A
				alu.RLC(alu.a);
				break;
			case 0x08: // RRC B
				alu.RRC(alu.b);
				break;
			case 0x09: // RRC C
				alu.RRC(alu.c);
				break;
			case 0x0A: // RRC D
				alu.RRC(alu.d);
				break;
			case 0x0B: // RRC E
				alu.RRC(alu.e);
				break;
			case 0x0C: // RRC H
				alu.RRC(alu.h);
				break;
			case 0x0D: // RRC L
				alu.RRC(alu.l);
				break;
			case 0x0E: // RRC (HL)
				break;
			case 0x0F: // RRC A
				alu.RRC(alu.a);
				break;

			// 0x10 - 0x1F
			case 0x10: // RL B
				alu.RL(alu.b);
				break;
			case 0x11: // RL C
				alu.RL(alu.c);
				break;
			case 0x12: // RL D
				alu.RL(alu.d);
				break;
			case 0x13: // RL E
				alu.RL(alu.e);
				break;
			case 0x14: // RL H
				alu.RL(alu.h);
				break;
			case 0x15: // RL L
				alu.RL(alu.l);
				break;
			case 0x16: // RL (HL)
				break;
			case 0x17: // RL A
				alu.RL(alu.a);
				break;
			case 0x18: // RR B
				alu.RR(alu.b);
				break;
			case 0x19: // RR C
				alu.RR(alu.c);
				break;
			case 0x1A: // RR D
				alu.RR(alu.d);
				break;
			case 0x1B: // RR E
				alu.RR(alu.e);
				break;
			case 0x1C: // RR H
				alu.RR(alu.h);
				break;
			case 0x1D: // RR L
				alu.RR(alu.l);
				break;
			case 0x1E: // RR (HL)
				break;
			case 0x1F: // RR A
				alu.RR(alu.a);
				break;
			
			// 0x20 - 0x2F
			case 0x20: // SLA B
				alu.SLA(alu.b);
				break;
			case 0x21: // SLA C
				alu.SLA(alu.c);
				break;
			case 0x22: // SLA D
				alu.SLA(alu.d);
				break;
			case 0x23: // SLA E
				alu.SLA(alu.e);
				break;
			case 0x24: // SLA H
				alu.SLA(alu.h);
				break;
			case 0x25: // SLA L
				alu.SLA(alu.l);
				break;
			case 0x26: // SLA (HL)
				break;
			case 0x27: // SLA A
				alu.SLA(alu.a);
				break;
			case 0x28: // SRA B
				alu.SRA(alu.b);
				break;
			case 0x29: // SRA C
				alu.SRA(alu.c);
				break;
			case 0x2A: // SRA D
				alu.SRA(alu.d);
				break;
			case 0x2B: // SRA E
				alu.SRA(alu.e);
				break;
			case 0x2C: // SRA H
				alu.SRA(alu.h);
				break;
			case 0x2D: // SRA L
				alu.SRA(alu.l);
				break;
			case 0x2E: // SRA (HL)
				break;
			case 0x2F: // SRA A
				alu.SRA(alu.a);
				break;

			// 0x30 - 0x3F
			case 0x30: // SWAP B
				alu.SWAP(alu.b);
				break;
			case 0x31: // SWAP C
				alu.SWAP(alu.c);
				break;
			case 0x32: // SWAP D
				alu.SWAP(alu.d);
				break;
			case 0x33: // SWAP E
				alu.SWAP(alu.e);
				break;
			case 0x34: // SWAP H
				alu.SWAP(alu.h);
				break;
			case 0x35: // SWAP L
				alu.SWAP(alu.l);
				break;
			case 0x36: // SWAP (HL)
				break;
			case 0x37: // SWAP A
				alu.SWAP(alu.a);
				break;
			case 0x38: // SRL B
				alu.SRL(alu.b);
				break;
			case 0x39: // SRL C
				alu.SRL(alu.c);
				break;
			case 0x3A: // SRL D
				alu.SRL(alu.d);
				break;
			case 0x3B: // SRL E
				alu.SRL(alu.e);
				break;
			case 0x3C: // SRL H
				alu.SRL(alu.h);
				break;
			case 0x3D: // SRL L
				alu.SRL(alu.l);
				break;
			case 0x3E: // SRL (HL)
				break;
			case 0x3F: // SRL A
				alu.SRL(alu.a);
				break;
		
			// 0x40 - 0x4F
			case 0x40: // BIT 0, B
				alu.BIT(0x0, alu.b);
				break;
			case 0x41: // BIT 0, C
				alu.BIT(0x0, alu.c);
				break;
			case 0x42: // BIT 0, D
				alu.BIT(0x0, alu.d);
				break;
			case 0x43: // BIT 0, E
				alu.BIT(0x0, alu.e);
				break;
			case 0x44: // BIT 0, H
				alu.BIT(0x0, alu.h);
				break;
			case 0x45: // BIT 0, L
				alu.BIT(0x0, alu.l);
				break;
			case 0x46: // BIT 0, (HL)
				break;
			case 0x47: // BIT 0, A
				alu.BIT(0x0, alu.a);
				break;
			case 0x48: // BIT 1, B
				alu.BIT(0x1, alu.b);
				break;
			case 0x49: // BIT 1, C
				alu.BIT(0x1, alu.c);
				break;
			case 0x4A: // BIT 1, D
				alu.BIT(0x1, alu.d);
				break;
			case 0x4B: // BIT 1, E
				alu.BIT(0x1, alu.e);
				break;
			case 0x4C: // BIT 1, H
				alu.BIT(0x1, alu.h);
				break;
			case 0x4D: // BIT 1, L
				alu.BIT(0x1, alu.l);
				break;
			case 0x4E: // BIT 1, (HL)
				break;
			case 0x4F: // BIT 1, A
				alu.BIT(0x1, alu.a);
				break;
		
			// 0x50 - 0x5F
			case 0x50: // BIT 2, B
				alu.BIT(0x2, alu.b);
				break;
			case 0x51: // BIT 2, C
				alu.BIT(0x2, alu.c);
				break;
			case 0x52: // BIT 2, D
				alu.BIT(0x2, alu.d);
				break;
			case 0x53: // BIT 2, E
				alu.BIT(0x2, alu.e);
				break;
			case 0x54: // BIT 2, H
				alu.BIT(0x2, alu.h);
				break;
			case 0x55: // BIT 2, L
				alu.BIT(0x2, alu.l);
				break;
			case 0x56: // BIT 2, (HL)
				break;
			case 0x57: // BIT 2, A
				alu.BIT(0x2, alu.a);
				break;
			case 0x58: // BIT 3, B
				alu.BIT(0x3, alu.b);
				break;
			case 0x59: // BIT 3, C
				alu.BIT(0x3, alu.c);
				break;
			case 0x5A: // BIT 3, D
				alu.BIT(0x3, alu.d);
				break;
			case 0x5B: // BIT 3, E
				alu.BIT(0x3, alu.e);
				break;
			case 0x5C: // BIT 3, H	
				alu.BIT(0x3, alu.h);
				break;
			case 0x5D: // BIT 3, L
				alu.BIT(0x3, alu.l);
				break;
			case 0x5E: // BIT 3, (HL)
				break;
			case 0x5F: // BIT 3, A
				alu.BIT(0x3, alu.a);
				break;

			// 0x60 - 0x6F
			case 0x60: // BIT 4, B
				alu.BIT(0x4, alu.b);
				break;
			case 0x61: // BIT 4, C
				alu.BIT(0x4, alu.c);
				break;
			case 0x62: // BIT 4, D
				alu.BIT(0x4, alu.d);
				break;
			case 0x63: // BIT 4, E
				alu.BIT(0x4, alu.e);
				break;
			case 0x64: // BIT 4, H
				alu.BIT(0x4, alu.h);
				break;
			case 0x65: // BIT 4, L
				alu.BIT(0x4, alu.l);
				break;
			case 0x66: // BIT 4, (HL)
				break;
			case 0x67: // BIT 4, A
				alu.BIT(0x4, alu.a);
				break;
			case 0x68: // BIT 5, B
				alu.BIT(0x5, alu.b);
				break;
			case 0x69: // BIT 5, C
				alu.BIT(0x5, alu.c);
				break;
			case 0x6A: // BIT 5, D
				alu.BIT(0x5, alu.d);
				break;
			case 0x6B: // BIT 5, E
				alu.BIT(0x5, alu.e);
				break;
			case 0x6C: // BIT 5, H
				alu.BIT(0x5, alu.h);
				break;
			case 0x6D: // BIT 5, L
				alu.BIT(0x5, alu.l);
				break;
			case 0x6E: // BIT 5, (HL)
				break;
			case 0x6F: // BIT 5, A
				alu.BIT(0x5, alu.a);
				break;

			// 0x70 - 0x7F
			case 0x70: // BIT 6, B
				alu.BIT(0x6, alu.b);
				break;
			case 0x71: // BIT 6, C
				alu.BIT(0x6, alu.c);
				break;
			case 0x72: // BIT 6, D
				alu.BIT(0x6, alu.d);
				break;
			case 0x73: // BIT 6, E
				alu.BIT(0x6, alu.e);
				break;
			case 0x74: // BIT 6, H
				alu.BIT(0x6, alu.h);
				break;
			case 0x75: // BIT 6, L
				alu.BIT(0x6, alu.l);
				break;
			case 0x76: // BIT 6, (HL)
				break;
			case 0x77: // BIT 6, A
				alu.BIT(0x6, alu.a);
				break;
			case 0x78: // BIT 7, B
				alu.BIT(0x7, alu.b);
				break;
			case 0x79: // BIT 7, C
				alu.BIT(0x7, alu.c);
				break;
			case 0x7A: // BIT 7, D
				alu.BIT(0x7, alu.d);
				break;
			case 0x7B: // BIT 7, E
				alu.BIT(0x7, alu.e);
				break;
			case 0x7C: // BIT 7, H
				alu.BIT(0x7, alu.h);
				break;
			case 0x7D: // BIT 7, L
				alu.BIT(0x7, alu.l);
				break;
			case 0x7E: // BIT 7, (HL)
				break;
			case 0x7F: // BIT 7, A
				alu.BIT(0x7, alu.a);
				break;

			// 0x80 - 0x8F
			case 0x80: // RES 0, B
				alu.RES(0x0, alu.b);
				break;
			case 0x81: // RES 0, C
				alu.RES(0x0, alu.c);
				break;
			case 0x82: // RES 0, D
				alu.RES(0x0, alu.d);
				break;
			case 0x83: // RES 0, E
				alu.RES(0x0, alu.e);
				break;
			case 0x84: // RES 0, H
				alu.RES(0x0, alu.h);
				break;
			case 0x85: // RES 0, L
				alu.RES(0x0, alu.l);
				break;
			case 0x86: // RES 0, (HL)
				break;
			case 0x87: // RES 0, A
				alu.RES(0x0, alu.a);
				break;
			case 0x88: // RES 1, B
				alu.RES(0x1, alu.b);
				break;
			case 0x89: // RES 1, C
				alu.RES(0x1, alu.c);
				break;
			case 0x8A: // RES 1, D
				alu.RES(0x1, alu.d);
				break;
			case 0x8B: // RES 1, E
				alu.RES(0x1, alu.e);
				break;
			case 0x8C: // RES 1, H
				alu.RES(0x1, alu.h);
				break;
			case 0x8D: // RES 1, L
				alu.RES(0x1, alu.l);
				break;
			case 0x8E: // RES 1, (HL)
				break;
			case 0x8F: // RES 1, A
				alu.RES(0x1, alu.a);
				break;

			// 0x90 - 0x9F
			case 0x90: // RES 2, B
				alu.RES(0x2, alu.b);
				break;
			case 0x91: // RES 2, C
				alu.RES(0x2, alu.c);
				break;
			case 0x92: // RES 2, D
				alu.RES(0x2, alu.d);
				break;
			case 0x93: // RES 2, E
				alu.RES(0x2, alu.e);
				break;
			case 0x94: // RES 2, H
				alu.RES(0x2, alu.h);
				break;
			case 0x95: // RES 2, L
				alu.RES(0x2, alu.l);
				break;
			case 0x96: // RES 2, (HL)
				break;
			case 0x97: // RES 2, A
				alu.RES(0x2, alu.a);
				break;
			case 0x98: // RES 3, B
				alu.RES(0x3, alu.b);
				break;
			case 0x99: // RES 3, C
				alu.RES(0x3, alu.c);
				break;
			case 0x9A: // RES 3, D
				alu.RES(0x3, alu.d);
				break;
			case 0x9B: // RES 3, E
				alu.RES(0x3, alu.e);
				break;
			case 0x9C: // RES 3, H
				alu.RES(0x3, alu.h);
				break;
			case 0x9D: // RES 3, L
				alu.RES(0x3, alu.l);
				break; 
			case 0x9E: // RES 3, (HL)
				break;
			case 0x9F: // RES 3, A
				alu.RES(0x3, alu.a);
				break;

			// 0xA0 - 0xAF
			case 0xA0: // RES 4, B
				alu.RES(0x4, alu.b);
				break;
			case 0xA1: // RES 4, C
				alu.RES(0x4, alu.c);
				break;
			case 0xA2: // RES 4, D
				alu.RES(0x4, alu.d);
				break;
			case 0xA3: // RES 4, E
				alu.RES(0x4, alu.e);
				break;
			case 0xA4: // RES 4, H
				alu.RES(0x4, alu.h);
				break;
			case 0xA5: // RES 4, L
				alu.RES(0x4, alu.l);
				break;
			case 0xA6: // RES 4, (HL)
				break;
			case 0xA7: // RES 4, A
				alu.RES(0x4, alu.a);
				break;
			case 0xA8: // RES 5, B
				alu.RES(0x5, alu.b);
				break;
			case 0xA9: // RES 5, C
				alu.RES(0x5, alu.c);
				break;
			case 0xAA: // RES 5, D
				alu.RES(0x5, alu.d);
				break;
			case 0xAB: // RES 5, E
				alu.RES(0x5, alu.e);
				break;
			case 0xAC: // RES 5, H
				alu.RES(0x5, alu.h);
				break;
			case 0xAD: // RES 5, L
				alu.RES(0x5, alu.l);
				break;
			case 0xAE: // RES 5, (HL)
				break;
			case 0xAF: // RES 5, A
				alu.RES(0x5, alu.a);
				break;
			
			// 0xB0 - 0xBF
			case 0xB0: // RES 6, B
				alu.RES(0x6, alu.b);
				break;
			case 0xB1: // RES 6, C
				alu.RES(0x6, alu.c);
				break;
			case 0xB2: // RES 6, D
				alu.RES(0x6, alu.d);
				break;
			case 0xB3: // RES 6, E
				alu.RES(0x6, alu.e);
				break;
			case 0xB4: // RES 6, H
				alu.RES(0x6, alu.h);
				break;
			case 0xB5: // RES 6, L
				alu.RES(0x6, alu.l);
				break;
			case 0xB6: // RES 6, (HL)
				break;
			case 0xB7: // RES 6, A
				alu.RES(0x6, alu.a);
				break;
			case 0xB8: // RES 7, B
				alu.RES(0x7, alu.b);
				break;
			case 0xB9: // RES 7, C
				alu.RES(0x7, alu.c);
				break;
			case 0xBA: // RES 7, D
				alu.RES(0x7, alu.d);
				break;
			case 0xBB: // RES 7, E
				alu.RES(0x7, alu.e);
				break;
			case 0xBC: // RES 7, H
				alu.RES(0x7, alu.h);
				break;
			case 0xBD: // RES 7, L
				alu.RES(0x7, alu.l);
				break;
			case 0xBE: // RES 7, (HL)
				break;
			case 0xBF: // RES 7, A
				alu.RES(0x7, alu.a);
				break;
			
			// 0xC0 - 0xCF
			case 0xC0: // SET 0, B
				alu.SET(0x0, alu.b);
				break;
			case 0xC1: // SET 0, C
				alu.SET(0x0, alu.c);
				break;
			case 0xC2: // SET 0, D
				alu.SET(0x0, alu.d);
				break;
			case 0xC3: // SET 0, E
				alu.SET(0x0, alu.e);
				break;
			case 0xC4: // SET 0, H
				alu.SET(0x0, alu.h);
				break;
			case 0xC5: // SET 0, L
				alu.SET(0x0, alu.l);
				break;
			case 0xC6: // SET 0, (HL)
				break;
			case 0xC7: // SET 0, A
				alu.SET(0x0, alu.a);
				break;
			case 0xC8: // SET 1, B
				alu.SET(0x1, alu.b);
				break;
			case 0xC9: // SET 1, C
				alu.SET(0x1, alu.c);
				break;
			case 0xCA: // SET 1, D
				alu.SET(0x1, alu.d);
				break;
			case 0xCB: // SET 1, E
				alu.SET(0x1, alu.e);
				break;
			case 0xCC: // SET 1, H
				alu.SET(0x1, alu.h);
				break;
			case 0xCD: // SET 1, L
				alu.SET(0x1, alu.l);
				break;
			case 0xCE: // SET 1, (HL)
				break;
			case 0xCF: // SET 1, A
				alu.SET(0x1, alu.a);
				break;

			// 0xD0 - 0xDF
			case 0xD0: // SET 2, B
				alu.SET(0x2, alu.b);
				break;
			case 0xD1: // SET 2, C
				alu.SET(0x2, alu.c);
				break;
			case 0xD2: // SET 2, D
				alu.SET(0x2, alu.d);
				break;
			case 0xD3: // SET 2, E
				alu.SET(0x2, alu.e);
				break;
			case 0xD4: // SET 2, H
				alu.SET(0x2, alu.h);
				break;
			case 0xD5: // SET 2, L
				alu.SET(0x2, alu.l);
				break;
			case 0xD6: // SET 2, (HL)
				break;
			case 0xD7: // SET 2, A
				alu.SET(0x2, alu.a);
				break;
			case 0xD8: // SET 3, B
				alu.SET(0x3, alu.b);
				break;
			case 0xD9: // SET 3, C
				alu.SET(0x3, alu.c);
				break;
			case 0xDA: // SET 3, D
				alu.SET(0x3, alu.d);
				break;
			case 0xDB: // SET 3, E
				alu.SET(0x3, alu.e);
				break;
			case 0xDC: // SET 3, H
				alu.SET(0x3, alu.h);
				break;
			case 0xDD: // SET 3, L
				alu.SET(0x3, alu.l);
				break;
			case 0xDE: // SET 3, (HL)
				break;
			case 0xDF: // SET 3, A
				alu.SET(0x3, alu.a);
				break;

			// 0xE0 - 0xEF
			case 0xE0: // SET 4, B
				alu.SET(0x4, alu.b);
				break;
			case 0xE1: // SET 4, C
				alu.SET(0x4, alu.c);
				break;
			case 0xE2: // SET 4, D
				alu.SET(0x4, alu.d);
				break;
			case 0xE3: // SET 4, E
				alu.SET(0x4, alu.e);
				break;
			case 0xE4: // SET 4, H
				alu.SET(0x4, alu.h);
				break;
			case 0xE5: // SET 4, L
				alu.SET(0x4, alu.l);
				break;
			case 0xE6: // SET 4, (HL)
				break;
			case 0xE7: // SET 4, A
				alu.SET(0x4, alu.a);
				break;
			case 0xE8: // SET 5, B
				alu.SET(0x5, alu.b);
				break;
			case 0xE9: // SET 5, C
				alu.SET(0x5, alu.c);
				break;
			case 0xEA: // SET 5, D
				alu.SET(0x5, alu.d);
				break;
			case 0xEB: // SET 5, E
				alu.SET(0x5, alu.e);
				break;
			case 0xEC: // SET 5, H
				alu.SET(0x5, alu.h);
				break;
			case 0xED: // SET 5, L
				alu.SET(0x5, alu.l);
				break;
			case 0xEE: // SET 5, (HL)
				break;
			case 0xEF: // SET 5, A
				alu.SET(0x5, alu.a);
				break;
			
			// 0xF0 - 0xFF
			case 0xF0: // SET 6, B
				alu.SET(0x6, alu.b);
				break;
			case 0xF1: // SET 6, C
				alu.SET(0x6, alu.c);
				break;
			case 0xF2: // SET 6, D
				alu.SET(0x6, alu.d);
				break;
			case 0xF3: // SET 6, E
				alu.SET(0x6, alu.e);
				break;
			case 0xF4: // SET 6, H
				alu.SET(0x6, alu.h);
				break;
			case 0xF5: // SET 6, L
				alu.SET(0x6, alu.l);
				break;
			case 0xF6: // SET 6, (HL)
				break;
			case 0xF7: // SET 6, A
				alu.SET(0x6, alu.a);
				break;
			case 0xF8: // SET 7, B
				alu.SET(0x7, alu.b);
				break;
			case 0xF9: // SET 7, C
				alu.SET(0x7, alu.c);
				break;
			case 0xFA: // SET 7, D
				alu.SET(0x7, alu.d);
				break;
			case 0xFB: // SET 7, E
				alu.SET(0x7, alu.e);
				break;
			case 0xFC: // SET 7, H
				alu.SET(0x7, alu.h);
				break;
			case 0xFD: // SET 7, L
				alu.SET(0x7, alu.l);
				break;
			case 0xFE: // SET 7, (HL)
				break;
			case 0xFF: // SET 7, A
				alu.SET(0x7, alu.a);
				break;

			default: // TODO: Error Log Data Here
				break;
		}
	}
}