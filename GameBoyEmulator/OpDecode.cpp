#include "ControlUnit.h"
#include "MemoryBus.h"
#include "ArithmeticLogicUnit.h"
#include "Register.h"
#include "RegisterFile.h"

namespace CPU
{
	// If this becomes hard to maintain consider breaking up nibble
	// Special thanks to https://gbdev.io/gb-opcodes/optables/
	void ControlUnit::decode(uint8_t opcode)
	{
		if (opcode == 0xCB)
		{
			registers.pc.set(registers.pc.get() + 1);
			decodeCBIns();
			return;
		}
#pragma region Main OP Codes

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
				INC(registers.bc);
				break;
			case 0x04: // INC B
				INC(registers.b);
				break;
			case 0x05: // DEC B
				DEC(registers.b);
				break;
			case 0x06: // LD B, d8
				break;
			case 0x07: // RLCA
				RLCA();
				break;
			case 0x08: // LD (a16), SP
				break;
			case 0x09: // ADD HL, BC
				ADD(registers.bc);
				break;
			case 0x0A: // LD A, (BC)
				break;
			case 0x0B: // DEC BC
				DEC(registers.bc);
				break;
			case 0x0C: // INC C
				INC(registers.c);
				break;
			case 0x0D: // DEC C
				DEC(registers.c);
				break;
			case 0x0E: // LD C, d8
				break;
			case 0x0F: // RRCA
				RRCA();
				break;

			// 0x10 - 0x1F
			case 0x10: // STOP 0
				break;
			case 0x11: // LD DE, d16
				break;
			case 0x12: // LD (DE), A
				break;
			case 0x13: // INC DE
				INC(registers.de);
				break;
			case 0x14: // INC D
				INC(registers.d);
				break;
			case 0x15: // DEC D
				DEC(registers.d);
				break;
			case 0x16: // LD D, d8
				break;
			case 0x17: // RLA
				RLA();
				break;
			case 0x18: // JR r8
				break;
			case 0x19: // ADD HL, DE
				ADD(registers.de);
				break;
			case 0x1A: // LD A, (DE)
				break;
			case 0x1B: // DEC DE
				DEC(registers.de);
				break;
			case 0x1C: // INC E
				INC(registers.e);
				break;
			case 0x1D: // DEC E
				DEC(registers.e);
				break;
			case 0x1E: // LD E, d8
				break;
			case 0x1F: // RRA
				RRA();
				break;

			// 0x20 - 0x2F
			case 0x20: // JR NZ, r8
				break;
			case 0x21: // LD HL, d16
				break;
			case 0x22: // LD (HL+), A
				break;
			case 0x23: // INC HL
				INC(registers.hl);
				break;
			case 0x24: // INC H
				INC(registers.h);
				break;
			case 0x25: // DEC H
				DEC(registers.h);
				break;
			case 0x26: // LD H, d8
				break;
			case 0x27: // DAA
				break;
			case 0x28: // JR Z, r8
				break;
			case 0x29: // ADD HL, HL
				ADD(registers.hl);
				break;
			case 0x2A: // LD A, (HL+)
				break;
			case 0x2B: // DEC HL
				DEC(registers.hl);
				break;
			case 0x2C: // INC L
				INC(registers.l);
				break;
			case 0x2D: // DEC L
				DEC(registers.l);
				break;
			case 0x2E: // LD L, d8
				break;
			case 0x2F: // CPL
				CPL();
				break;

			// 0x30 - 0x3F
			case 0x30: // JR NC, r8
				break;
			case 0x31: // LD SP, d16
				break;
			case 0x32: // LD (HL-), A
				break;
			case 0x33: // INC SP
				INC(registers.sp);
				break;
			case 0x34: // INC (HL)
				memory.write(registers.hl.get(), INC(memory.read(registers.hl.get())));
				break;
			case 0x35: // DEC (HL)
				memory.write(registers.hl.get(), DEC(memory.read(registers.hl.get())));
				break;
			case 0x36: // LD (HL), d8
				break;
			case 0x37: // SCF
				break;
			case 0x38: // JR C, r8
				break;
			case 0x39: // ADD HL, SP
				ADD(registers.sp);
				break;
			case 0x3A: // LD A, (HL-)
				break;
			case 0x3B: // DEC SP
				DEC(registers.sp);
				break;
			case 0x3C: // INC A
				INC(registers.a);
				break;
			case 0x3D: // DEC A
				DEC(registers.a);
				break;
			case 0x3E: // LD A, d8
				break;
			case 0x3F: // CCF
				break;

			// 0x40 - 0x4F
			case 0x40: // LD B, B
				LD(registers.b, registers.b);
				break;
			case 0x41: // LD B, C
				LD(registers.b, registers.c);
				break;
			case 0x42: // LD B, D
				LD(registers.b, registers.d);
				break;
			case 0x43: // LD B, E
				LD(registers.b, registers.e);
				break;
			case 0x44: // LD B, H
				LD(registers.b, registers.h);
				break;
			case 0x45: // LD B, L
				LD(registers.b, registers.l);
				break;
			case 0x46: // LD B, (HL)
				LD(registers.b, memory.read(registers.hl.get()));
				break;
			case 0x47: // LD B, A
				LD(registers.b, registers.a);
				break;
			case 0x48: // LD C, B
				LD(registers.c, registers.b);
				break;
			case 0x49: // LD C, C
				LD(registers.c, registers.c);
				break;
			case 0x4A: // LD C, D
				LD(registers.c, registers.d);
				break;
			case 0x4B: // LD C, E
				LD(registers.c, registers.e);
				break;
			case 0x4C: // LD C, H
				LD(registers.c, registers.h);
				break;
			case 0x4D: // LD C, L
				LD(registers.c, registers.l);
				break;
			case 0x4E: // LD C, (HL)
				LD(registers.c, memory.read(registers.hl.get()));
				break;
			case 0x4F: // LD C, A
				LD(registers.c, registers.a);
				break;

			// 0x50 - 0x5F
			case 0x50: // LD D, B
				LD(registers.d, registers.b);
				break;
			case 0x51: // LD D, C
				LD(registers.d, registers.c);
				break;
			case 0x52: // LD D, D
				LD(registers.d, registers.d);
				break;
			case 0x53: // LD D, E
				LD(registers.d, registers.e);
				break;
			case 0x54: // LD D, H
				LD(registers.d, registers.h);
				break;
			case 0x55: // LD D, L
				LD(registers.d, registers.l);
				break;
			case 0x56: // LD D, (HL)
				LD(registers.d, memory.read(registers.hl.get()));
				break;
			case 0x57: // LD D, A
				LD(registers.d, registers.a);
				break;
			case 0x58: // LD E, B
				LD(registers.e, registers.b);
				break;
			case 0x59: // LD E, C
				LD(registers.e, registers.c);
				break;
			case 0x5A: // LD E, D
				LD(registers.e, registers.d);
				break;
			case 0x5B: // LD E, E
				LD(registers.e, registers.e);
				break;
			case 0x5C: // LD E, H
				LD(registers.e, registers.h);
				break;
			case 0x5D: // LD E, L
				LD(registers.e, registers.l);
				break;
			case 0x5E: // LD E, (HL)
				LD(registers.e, memory.read(registers.hl.get()));
				break;
			case 0x5F: // LD E, A
				LD(registers.e, registers.a);
				break;

			// 0x60 - 0x6F
			case 0x60: // LD H, B
				LD(registers.h, registers.b);
				break;
			case 0x61: // LD H, C
				LD(registers.h, registers.c);
				break;
			case 0x62: // LD H, D
				LD(registers.h, registers.d);
				break;
			case 0x63: // LD H, E
				LD(registers.h, registers.e);
				break;
			case 0x64: // LD H, H
				LD(registers.h, registers.h);
				break;
			case 0x65: // LD H, L
				LD(registers.h, registers.l);
				break;
			case 0x66: // LD H, (HL)
				LD(registers.h, memory.read(registers.hl.get()));
				break;
			case 0x67: // LD H, A
				LD(registers.h, registers.a);
				break;
			case 0x68: // LD L, B
				LD(registers.l, registers.b);
				break;
			case 0x69: // LD L, C
				LD(registers.l, registers.c);
				break;
			case 0x6A: // LD L, D
				LD(registers.l, registers.d);
				break;
			case 0x6B: // LD L, E
				LD(registers.l, registers.e);
				break;
			case 0x6C: // LD L, H
				LD(registers.l, registers.h);
				break;
			case 0x6D: // LD L, L
				LD(registers.l, registers.l);
				break;
			case 0x6E: // LD L, (HL)
				LD(registers.l, memory.read(registers.hl.get()));
				break;
			case 0x6F: // LD L, A
				LD(registers.l, registers.a);
				break;

			// 0x70 - 0x7F
			case 0x70: // LD (HL), B
				memory.write(registers.hl.get(), registers.b.get());
				break;
			case 0x71: // LD (HL), C
				memory.write(registers.hl.get(), registers.c.get());
				break;
			case 0x72: // LD (HL), D
				memory.write(registers.hl.get(), registers.d.get());
				break;
			case 0x73: // LD (HL), E
				memory.write(registers.hl.get(), registers.e.get());
				break;
			case 0x74: // LD (HL), H
				memory.write(registers.hl.get(), registers.h.get());
				break;
			case 0x75: // LD (HL), L
				memory.write(registers.hl.get(), registers.l.get());
				break;
			case 0x76: // HALT
				break;
			case 0x77: // LD (HL), A
				memory.write(registers.hl.get(), registers.a.get());
				break;
			case 0x78: // LD A, B
				LD(registers.a, registers.b);
				break;
			case 0x79: // LD A, C
				LD(registers.a, registers.c);
				break;
			case 0x7A: // LD A, D
				LD(registers.a, registers.d);
				break;
			case 0x7B: // LD A, E
				LD(registers.a, registers.e);
				break;
			case 0x7C: // LD A, H
				LD(registers.a, registers.h);
				break;
			case 0x7D: // LD A, L
				LD(registers.a, registers.l);
				break;
			case 0x7E: // LD A, (HL)
				LD(registers.a, memory.read(registers.hl.get()));
				break;
			case 0x7F: // LD A, A
				LD(registers.a, registers.a);
				break;

			// 0x80 - 0x8F
			case 0x80: // ADD A, B
				ADD(registers.b);
				break;
			case 0x81: // ADD A, C
				ADD(registers.c);
				break;
			case 0x82: // ADD A, D
				ADD(registers.d);
				break;
			case 0x83: // ADD A, E
				ADD(registers.e);
				break;
			case 0x84: // ADD A, H
				ADD(registers.h);
				break;
			case 0x85: // ADD A, L
				ADD(registers.l);
				break;
			case 0x86: // ADD A, (HL)
				ADD(memory.read(registers.hl.get()));
				break;
			case 0x87: // ADD A, A
				ADD(registers.a);
				break;
			case 0x88: // ADC A, B
				ADC(registers.b);
				break;
			case 0x89: // ADC A, C
				ADC(registers.c);
				break;
			case 0x8A: // ADC A, D
				ADC(registers.d);
				break;
			case 0x8B: // ADC A, E
				ADC(registers.e);
				break;
			case 0x8C: // ADC A, H
				ADC(registers.h);
				break;
			case 0x8D: // ADC A, L
				ADC(registers.l);
				break;
			case 0x8E: // ADC A, (HL)
				ADC(memory.read(registers.hl.get()));
				break;
			case 0x8F: // ADC A, A
				ADC(registers.a);
				break;

			// 0x90 - 0x9F
			case 0x90: // SUB A, B
				SUB(registers.b);
				break;
			case 0x91: // SUB A, C
				SUB(registers.c);
				break;
			case 0x92: // SUB A, D
				SUB(registers.d);
				break;
			case 0x93: // SUB A, E
				SUB(registers.e);
				break;
			case 0x94: // SUB A, H
				SUB(registers.h);
				break;
			case 0x95: // SUB A, L
				SUB(registers.l);
				break;
			case 0x96: // SUB A, (HL)
				SUB(memory.read(registers.hl.get()));
				break;
			case 0x97: // SUB A, A
				SUB(registers.a);
				break;
			case 0x98: // SBC A, B
				SBC(registers.b);
				break;
			case 0x99: // SBC A, C
				SBC(registers.c);
				break;
			case 0x9A: // SBC A, D
				SBC(registers.d);
				break;
			case 0x9B: // SBC A, E
				SBC(registers.e);
				break;
			case 0x9C: // SBC A, H
				SBC(registers.h);
				break;
			case 0x9D: // SBC A, L
				SBC(registers.l);
				break;
			case 0x9E: // SBC A, (HL)
				SBC(memory.read(registers.hl.get()));
				break;
			case 0x9F: // SBC A, A
				SBC(registers.a);
				break;

			// 0xA0 - 0xAF
			case 0xA0: // AND A, B
				AND(registers.b);
				break;
			case 0xA1: // AND A, C
				AND(registers.c);
				break;
			case 0xA2: // AND A, D
				AND(registers.d);
				break;
			case 0xA3: // AND A, E
				AND(registers.e);
				break;
			case 0xA4: // AND A, H
				AND(registers.h);
				break;
			case 0xA5: // AND A, L
				AND(registers.l);
				break;
			case 0xA6: // AND A, (HL)
				AND(memory.read(registers.hl.get()));
				break;
			case 0xA7: // AND A, A
				AND(registers.a);
				break;
			case 0xA8: // XOR A, B
				XOR(registers.b);
				break;
			case 0xA9: // XOR A, C
				XOR(registers.c);
				break;
			case 0xAA: // XOR A, D
				XOR(registers.d);
				break;
			case 0xAB: // XOR A, E
				XOR(registers.e);
				break;
			case 0xAC: // XOR A, H
				XOR(registers.h);
				break;
			case 0xAD: // XOR A, L
				XOR(registers.l);
				break;
			case 0xAE: // XOR A, (HL)
				XOR(memory.read(registers.hl.get()));
				break;
			case 0xAF: // XOR A, A
				XOR(registers.a);
				break;

			// 0xB0 - 0xBF
			case 0xB0: // OR A, B
				OR(registers.b);
				break;
			case 0xB1: // OR A, C
				OR(registers.c);
				break;
			case 0xB2: // OR A, D
				OR(registers.d);
				break;
			case 0xB3: // OR A, E
				OR(registers.e);
				break;
			case 0xB4: // OR A, H
				OR(registers.h);
				break;
			case 0xB5: // OR A, L
				OR(registers.l);
				break;
			case 0xB6: // OR A, (HL)
				OR(memory.read(registers.hl.get()));
				break;
			case 0xB7: // OR A, A
				OR(registers.a);
				break;
			case 0xB8: // CP A, B
				CP(registers.b);
				break;
			case 0xB9: // CP A, C
				CP(registers.c);
				break;
			case 0xBA: // CP A, D
				CP(registers.d);
				break;
			case 0xBB: // CP A, E
				CP(registers.e);
				break;
			case 0xBC: // CP A, H
				CP(registers.h);
				break;
			case 0xBD: // CP A, L
				CP(registers.l);
				break;
			case 0xBE: // CP A, (HL)
				CP(memory.read(registers.hl.get()));
				break;
			case 0xBF: // CP A, A
				CP(registers.a);
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

			// 0xF0 - 0xFF
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

			default: // TODO: Log Error Data Here or handle interrupt
				break;

		}
#pragma endregion

	}

	void ControlUnit::decodeCBIns()
	{
		uint8_t opcode = memory.read(registers.pc.get());

#pragma region CB OP Codes

		switch (opcode)
		{
			// 0x00 - 0x0F
			case 0x00: // RLC B
				RLC(registers.b);
				break;
			case 0x01: // RLC C
				RLC(registers.c);
				break;
			case 0x02: // RLC D
				RLC(registers.d);
				break;
			case 0x03: // RLC E
				RLC(registers.e);
				break;
			case 0x04: // RLC H
				RLC(registers.h);
				break;
			case 0x05: // RLC L
				RLC(registers.l);
				break;
			case 0x06: // RLC (HL)
				memory.write(registers.hl.get(), RLC(memory.read(registers.hl.get())));
				break;
			case 0x07: // RLC A
				RLC(registers.a);
				break;
			case 0x08: // RRC B
				RRC(registers.b);
				break;
			case 0x09: // RRC C
				RRC(registers.c);
				break;
			case 0x0A: // RRC D
				RRC(registers.d);
				break;
			case 0x0B: // RRC E
				RRC(registers.e);
				break;
			case 0x0C: // RRC H
				RRC(registers.h);
				break;
			case 0x0D: // RRC L
				RRC(registers.l);
				break;
			case 0x0E: // RRC (HL)
				memory.write(registers.hl.get(), RRC(memory.read(registers.hl.get())));
				break;
			case 0x0F: // RRC A
				RRC(registers.a);
				break;

			// 0x10 - 0x1F
			case 0x10: // RL B
				RL(registers.b);
				break;
			case 0x11: // RL C
				RL(registers.c);
				break;
			case 0x12: // RL D
				RL(registers.d);
				break;
			case 0x13: // RL E
				RL(registers.e);
				break;
			case 0x14: // RL H
				RL(registers.h);
				break;
			case 0x15: // RL L
				RL(registers.l);
				break;
			case 0x16: // RL (HL)
				memory.write(registers.hl.get(), RL(memory.read(registers.hl.get())));
				break;
			case 0x17: // RL A
				RL(registers.a);
				break;
			case 0x18: // RR B
				RL(registers.b);
				break;
			case 0x19: // RR C
				RR(registers.c);
				break;
			case 0x1A: // RR D
				RR(registers.d);
				break;
			case 0x1B: // RR E
				RR(registers.e);
				break;
			case 0x1C: // RR H
				RR(registers.h);
				break;
			case 0x1D: // RR L
				RR(registers.l);
				break;
			case 0x1E: // RR (HL)
				memory.write(registers.hl.get(), RR(memory.read(registers.hl.get())));
				break;
			case 0x1F: // RR A
				RR(registers.a);
				break;

			// 0x20 - 0x2F
			case 0x20: // SLA B
				SLA(registers.b);
				break;
			case 0x21: // SLA C
				SLA(registers.c);
				break;
			case 0x22: // SLA D
				SLA(registers.d);
				break;
			case 0x23: // SLA E
				SLA(registers.e);
				break;
			case 0x24: // SLA H
				SLA(registers.h);
				break;
			case 0x25: // SLA L
				SLA(registers.l);
				break;
			case 0x26: // SLA (HL)
				memory.write(registers.hl.get(), SLA(memory.read(registers.hl.get())));
				break;
			case 0x27: // SLA A
				SLA(registers.a);
				break;
			case 0x28: // SRA B
				SRA(registers.b);
				break;
			case 0x29: // SRA C
				SRA(registers.c);
				break;
			case 0x2A: // SRA D
				SRA(registers.d);
				break;
			case 0x2B: // SRA E
				SRA(registers.e);
				break;
			case 0x2C: // SRA H
				SRA(registers.h);
				break;
			case 0x2D: // SRA L
				SRA(registers.l);
				break;
			case 0x2E: // SRA (HL)
				memory.write(registers.hl.get(), SRA(memory.read(registers.hl.get())));
				break;
			case 0x2F: // SRA A
				SRA(registers.a);
				break;

			// 0x30 - 0x3F
			case 0x30: // SWAP B
				SWAP(registers.b);
				break;
			case 0x31: // SWAP C
				SWAP(registers.c);
				break;
			case 0x32: // SWAP D
				SWAP(registers.d);
				break;
			case 0x33: // SWAP E
				SWAP(registers.e);
				break;
			case 0x34: // SWAP H
				SWAP(registers.h);
				break;
			case 0x35: // SWAP L
				SWAP(registers.l);
				break;
			case 0x36: // SWAP (HL)
				memory.write(registers.hl.get(), SWAP(memory.read(registers.hl.get())));
				break;
			case 0x37: // SWAP A
				SWAP(registers.a);
				break;
			case 0x38: // SRL B
				SRL(registers.b);
				break;
			case 0x39: // SRL C
				SRL(registers.c);
				break;
			case 0x3A: // SRL D
				SRL(registers.d);
				break;
			case 0x3B: // SRL E
				SRL(registers.e);
				break;
			case 0x3C: // SRL H
				SRL(registers.h);
				break;
			case 0x3D: // SRL L
				SRL(registers.l);
				break;
			case 0x3E: // SRL (HL)
				memory.write(registers.hl.get(), SRL(memory.read(registers.hl.get())));
				break;
			case 0x3F: // SRL A
				SRL(registers.a);
				break;

			// 0x40 - 0x4F
			case 0x40: // BIT 0, B
				BIT(0x00, registers.b);
				break;
			case 0x41: // BIT 0, C
				BIT(0x00, registers.c);
				break;
			case 0x42: // BIT 0, D
				BIT(0x00, registers.d);
				break;
			case 0x43: // BIT 0, E
				BIT(0x00, registers.e);
				break;
			case 0x44: // BIT 0, H
				BIT(0x00, registers.h);
				break;
			case 0x45: // BIT 0, L
				BIT(0x00, registers.l);
				break;
			case 0x46: // BIT 0, (HL)
				BIT(0x00, memory.read(registers.hl.get()));
				break;
			case 0x47: // BIT 0, A
				BIT(0x00, registers.a);
				break;
			case 0x48: // BIT 1, B
				BIT(0x01, registers.b);
				break;
			case 0x49: // BIT 1, C
				BIT(0x01, registers.c);
				break;
			case 0x4A: // BIT 1, D
				BIT(0x01, registers.d);
				break;
			case 0x4B: // BIT 1, E
				BIT(0x01, registers.e);
				break;
			case 0x4C: // BIT 1, H
				BIT(0x01, registers.h);
				break;
			case 0x4D: // BIT 1, L
				BIT(0x01, registers.l);
				break;
			case 0x4E: // BIT 1, (HL)
				BIT(0x01, memory.read(registers.hl.get()));
				break;
			case 0x4F: // BIT 1, A
				BIT(0x01, registers.a);
				break;

			// 0x50 - 0x5F
			case 0x50: // BIT 2, B
				BIT(0x02, registers.b);
				break;
			case 0x51: // BIT 2, C
				BIT(0x02, registers.c);
				break;
			case 0x52: // BIT 2, D
				BIT(0x02, registers.d);
				break;
			case 0x53: // BIT 2, E
				BIT(0x02, registers.e);
				break;
			case 0x54: // BIT 2, H
				BIT(0x02, registers.h);
				break;
			case 0x55: // BIT 2, L
				BIT(0x02, registers.l);
				break;
			case 0x56: // BIT 2, (HL)
				BIT(0x02, memory.read(registers.hl.get()));
				break;
			case 0x57: // BIT 2, A
				BIT(0x02, registers.a);
				break;
			case 0x58: // BIT 3, B
				BIT(0x03, registers.b);
				break;
			case 0x59: // BIT 3, C
				BIT(0x03, registers.c);
				break;
			case 0x5A: // BIT 3, D
				BIT(0x03, registers.d);
				break;
			case 0x5B: // BIT 3, E
				BIT(0x03, registers.e);
				break;
			case 0x5C: // BIT 3, H	
				BIT(0x03, registers.h);
				break;
			case 0x5D: // BIT 3, L
				BIT(0x03, registers.l);
				break;
			case 0x5E: // BIT 3, (HL)
				BIT(0x03, memory.read(registers.hl.get()));
				break;
			case 0x5F: // BIT 3, A
				BIT(0x03, registers.a);
				break;

			// 0x60 - 0x6F
			case 0x60: // BIT 4, B
				BIT(0x04, registers.b);
				break;
			case 0x61: // BIT 4, C
				BIT(0x04, registers.c);
				break;
			case 0x62: // BIT 4, D
				BIT(0x04, registers.d);
				break;
			case 0x63: // BIT 4, E
				BIT(0x04, registers.e);
				break;
			case 0x64: // BIT 4, H
				BIT(0x04, registers.h);
				break;
			case 0x65: // BIT 4, L
				BIT(0x04, registers.l);
				break;
			case 0x66: // BIT 4, (HL)
				BIT(0x04, memory.read(registers.hl.get()));
				break;
			case 0x67: // BIT 4, A
				BIT(0x04, registers.a);
				break;
			case 0x68: // BIT 5, B
				BIT(0x05, registers.b);
				break;
			case 0x69: // BIT 5, C
				BIT(0x05, registers.c);
				break;
			case 0x6A: // BIT 5, D
				BIT(0x05, registers.d);
				break;
			case 0x6B: // BIT 5, E
				BIT(0x05, registers.e);
				break;
			case 0x6C: // BIT 5, H
				BIT(0x05, registers.h);
				break;
			case 0x6D: // BIT 5, L
				BIT(0x05, registers.l);
				break;
			case 0x6E: // BIT 5, (HL)
				BIT(0x05, memory.read(registers.hl.get()));
				break;
			case 0x6F: // BIT 5, A
				BIT(0x05, registers.a);
				break;

			// 0x70 - 0x7F
			case 0x70: // BIT 6, B
				BIT(0x06, registers.b);
				break;
			case 0x71: // BIT 6, C
				BIT(0x06, registers.c);
				break;
			case 0x72: // BIT 6, D
				BIT(0x06, registers.d);
				break;
			case 0x73: // BIT 6, E
				BIT(0x06, registers.e);
				break;
			case 0x74: // BIT 6, H
				BIT(0x06, registers.h);
				break;
			case 0x75: // BIT 6, L
				BIT(0x06, registers.l);
				break;
			case 0x76: // BIT 6, (HL)
				BIT(0x06, memory.read(registers.hl.get()));
				break;
			case 0x77: // BIT 6, A
				BIT(0x06, registers.a);
				break;
			case 0x78: // BIT 7, B
				BIT(0x07, registers.b);
				break;
			case 0x79: // BIT 7, C
				BIT(0x07, registers.c);
				break;
			case 0x7A: // BIT 7, D
				BIT(0x07, registers.d);
				break;
			case 0x7B: // BIT 7, E
				BIT(0x07, registers.e);
				break;
			case 0x7C: // BIT 7, H
				BIT(0x07, registers.h);
				break;
			case 0x7D: // BIT 7, L
				BIT(0x07, registers.l);
				break;
			case 0x7E: // BIT 7, (HL)
				BIT(0x07, memory.read(registers.hl.get()));
				break;
			case 0x7F: // BIT 7, A
				BIT(0x07, registers.a);
				break;

			// 0x80 - 0x8F
			case 0x80: // RES 0, B
				RES(0x00, registers.b);
				break;
			case 0x81: // RES 0, C
				RES(0x00, registers.c);
				break;
			case 0x82: // RES 0, D
				RES(0x00, registers.d);
				break;
			case 0x83: // RES 0, E
				RES(0x00, registers.e);
				break;
			case 0x84: // RES 0, H
				RES(0x00, registers.h);
				break;
			case 0x85: // RES 0, L
				RES(0x00, registers.l);
				break;
			case 0x86: // RES 0, (HL)
				memory.write(registers.hl.get(), RES(0x00, memory.read(registers.hl.get())));
				break;
			case 0x87: // RES 0, A
				RES(0x00, registers.a);
				break;
			case 0x88: // RES 1, B
				RES(0x01, registers.b);
				break;
			case 0x89: // RES 1, C
				RES(0x01, registers.c);
				break;
			case 0x8A: // RES 1, D
				RES(0x01, registers.d);
				break;
			case 0x8B: // RES 1, E
				RES(0x01, registers.e);
				break;
			case 0x8C: // RES 1, H
				RES(0x01, registers.h);
				break;
			case 0x8D: // RES 1, L
				RES(0x01, registers.l);
				break;
			case 0x8E: // RES 1, (HL)
				memory.write(registers.hl.get(), RES(0x01, memory.read(registers.hl.get())));
				break;
			case 0x8F: // RES 1, A
				RES(0x01, registers.a);
				break;

			// 0x90 - 0x9F
			case 0x90: // RES 2, B
				RES(0x02, registers.b);
				break;
			case 0x91: // RES 2, C
				RES(0x02, registers.c);
				break;
			case 0x92: // RES 2, D
				RES(0x02, registers.d);
				break;
			case 0x93: // RES 2, E
				RES(0x02, registers.e);
				break;
			case 0x94: // RES 2, H
				RES(0x02, registers.h);
				break;
			case 0x95: // RES 2, L
				RES(0x02, registers.l);
				break;
			case 0x96: // RES 2, (HL)
				memory.write(registers.hl.get(), RES(0x02, memory.read(registers.hl.get())));
				break;
			case 0x97: // RES 2, A
				RES(0x02, registers.a);
				break;
			case 0x98: // RES 3, B
				RES(0x03, registers.b);
				break;
			case 0x99: // RES 3, C
				RES(0x03, registers.c);
				break;
			case 0x9A: // RES 3, D
				RES(0x03, registers.d);
				break;
			case 0x9B: // RES 3, E
				RES(0x03, registers.e);
				break;
			case 0x9C: // RES 3, H
				RES(0x03, registers.h);
				break;
			case 0x9D: // RES 3, L
				RES(0x03, registers.l);
				break;
			case 0x9E: // RES 3, (HL)
				memory.write(registers.hl.get(), RES(0x03, memory.read(registers.hl.get())));
				break;
			case 0x9F: // RES 3, A
				RES(0x03, registers.a);
				break;
		
			// 0xA0 - 0xAF
			case 0xA0: // RES 4, B
				RES(0x04, registers.b);
				break;
			case 0xA1: // RES 4, C
				RES(0x04, registers.c);
				break;
			case 0xA2: // RES 4, D
				RES(0x04, registers.d);
				break;
			case 0xA3: // RES 4, E
				RES(0x04, registers.e);
				break;
			case 0xA4: // RES 4, H
				RES(0x04, registers.h);
				break;
			case 0xA5: // RES 4, L
				RES(0x04, registers.l);
				break;
			case 0xA6: // RES 4, (HL)
				memory.write(registers.hl.get(), RES(0x04, memory.read(registers.hl.get())));
				break;
			case 0xA7: // RES 4, A
				RES(0x04, registers.a);
				break;
			case 0xA8: // RES 5, B
				RES(0x05, registers.b);
				break;
			case 0xA9: // RES 5, C
				RES(0x05, registers.c);
				break;
			case 0xAA: // RES 5, D
				RES(0x05, registers.d);
				break;
			case 0xAB: // RES 5, E
				RES(0x05, registers.e);
				break;
			case 0xAC: // RES 5, H
				RES(0x05, registers.h);
				break;
			case 0xAD: // RES 5, L
				RES(0x05, registers.l);
				break;
			case 0xAE: // RES 5, (HL)
				memory.write(registers.hl.get(), RES(0x05, memory.read(registers.hl.get())));
				break;
			case 0xAF: // RES 5, A
				RES(0x05, registers.a);
				break;

			// 0xB0 - 0xBF
			case 0xB0: // RES 6, B
				RES(0x06, registers.b);
				break;
			case 0xB1: // RES 6, C
				RES(0x06, registers.c);
				break;
			case 0xB2: // RES 6, D
				RES(0x06, registers.d);
				break;
			case 0xB3: // RES 6, E
				RES(0x06, registers.e);
				break;
			case 0xB4: // RES 6, H
				RES(0x06, registers.h);
				break;
			case 0xB5: // RES 6, L
				RES(0x06, registers.l);
				break;
			case 0xB6: // RES 6, (HL)
				memory.write(registers.hl.get(), RES(0x06, memory.read(registers.hl.get())));
				break;
			case 0xB7: // RES 6, A
				RES(0x06, registers.a);
				break;
			case 0xB8: // RES 7, B
				RES(0x07, registers.b);
				break;
			case 0xB9: // RES 7, C
				RES(0x07, registers.c);
				break;
			case 0xBA: // RES 7, D
				RES(0x07, registers.d);
				break;
			case 0xBB: // RES 7, E
				RES(0x07, registers.e);
				break;
			case 0xBC: // RES 7, H
				RES(0x07, registers.h);
				break;
			case 0xBD: // RES 7, L
				RES(0x07, registers.l);
				break;
			case 0xBE: // RES 7, (HL)
				memory.write(registers.hl.get(), RES(0x07, memory.read(registers.hl.get())));
				break;
			case 0xBF: // RES 7, A
				RES(0x07, registers.a);
				break;

			// 0xC0 - 0xCF
			case 0xC0: // SET 0, B
				SET(0x00, registers.b);
				break;
			case 0xC1: // SET 0, C
				SET(0x00, registers.c);
				break;
			case 0xC2: // SET 0, D
				SET(0x00, registers.d);
				break;
			case 0xC3: // SET 0, E
				SET(0x00, registers.e);
				break;
			case 0xC4: // SET 0, H
				SET(0x00, registers.h);
				break;
			case 0xC5: // SET 0, L
				SET(0x00, registers.l);
				break;
			case 0xC6: // SET 0, (HL)
				memory.write(registers.hl.get(), SET(0x00, memory.read(registers.hl.get())));
				break;
			case 0xC7: // SET 0, A
				SET(0x00, registers.a);
				break;
			case 0xC8: // SET 1, B
				SET(0x01, registers.b);
				break;
			case 0xC9: // SET 1, C
				SET(0x01, registers.c);
				break;
			case 0xCA: // SET 1, D
				SET(0x01, registers.d);
				break;
			case 0xCB: // SET 1, E
				SET(0x01, registers.e);
				break;
			case 0xCC: // SET 1, H
				SET(0x01, registers.h);
				break;
			case 0xCD: // SET 1, L
				SET(0x01, registers.l);
				break;
			case 0xCE: // SET 1, (HL)
				memory.write(registers.hl.get(), SET(0x01, memory.read(registers.hl.get())));
				break;
			case 0xCF: // SET 1, A
				SET(0x01, registers.a);
				break;

			// 0xD0 - 0xDF
			case 0xD0: // SET 2, B
				SET(0x02, registers.b);
				break;
			case 0xD1: // SET 2, C
				SET(0x02, registers.c);
				break;
			case 0xD2: // SET 2, D
				SET(0x02, registers.d);
				break;
			case 0xD3: // SET 2, E
				SET(0x02, registers.e);
				break;
			case 0xD4: // SET 2, H
				SET(0x02, registers.h);
				break;
			case 0xD5: // SET 2, L
				SET(0x02, registers.l);
				break;
			case 0xD6: // SET 2, (HL)
				memory.write(registers.hl.get(), SET(0x02, memory.read(registers.hl.get())));
				break;
			case 0xD7: // SET 2, A
				SET(0x02, registers.a);
				break;
			case 0xD8: // SET 3, B
				SET(0x03, registers.b);
				break;
			case 0xD9: // SET 3, C
				SET(0x03, registers.c);
				break;
			case 0xDA: // SET 3, D
				SET(0x03, registers.d);
				break;
			case 0xDB: // SET 3, E
				SET(0x03, registers.e);
				break;
			case 0xDC: // SET 3, H
				SET(0x03, registers.h);
				break;
			case 0xDD: // SET 3, L
				SET(0x03, registers.l);
				break;
			case 0xDE: // SET 3, (HL)
				memory.write(registers.hl.get(), SET(0x03, memory.read(registers.hl.get())));
				break;
			case 0xDF: // SET 3, A
				SET(0x03, registers.a);
				break;

			// 0xE0 - 0xEF
			case 0xE0: // SET 4, B
				SET(0x04, registers.b);
				break;
			case 0xE1: // SET 4, C
				SET(0x04, registers.c);
				break;
			case 0xE2: // SET 4, D
				SET(0x04, registers.d);
				break;
			case 0xE3: // SET 4, E
				SET(0x04, registers.e);
				break;
			case 0xE4: // SET 4, H
				SET(0x04, registers.h);
				break;
			case 0xE5: // SET 4, L
				SET(0x04, registers.l);
				break;
			case 0xE6: // SET 4, (HL)
				memory.write(registers.hl.get(), SET(0x04, memory.read(registers.hl.get())));
				break;
			case 0xE7: // SET 4, A
				SET(0x04, registers.a);
				break;
			case 0xE8: // SET 5, B
				SET(0x05, registers.b);
				break;
			case 0xE9: // SET 5, C
				SET(0x05, registers.c);
				break;
			case 0xEA: // SET 5, D
				SET(0x05, registers.d);
				break;
			case 0xEB: // SET 5, E
				SET(0x05, registers.e);
				break;
			case 0xEC: // SET 5, H
				SET(0x05, registers.h);
				break;
			case 0xED: // SET 5, L
				SET(0x05, registers.l);
				break;
			case 0xEE: // SET 5, (HL)
				memory.write(registers.hl.get(), SET(0x05, memory.read(registers.hl.get())));
				break;
			case 0xEF: // SET 5, A
				SET(0x05, registers.a);
				break;

			// 0xF0 - 0xFF
			case 0xF0: // SET 6, B
				SET(0x06, registers.b);
				break;
			case 0xF1: // SET 6, C
				SET(0x06, registers.c);
				break;
			case 0xF2: // SET 6, D
				SET(0x06, registers.d);
				break;
			case 0xF3: // SET 6, E
				SET(0x06, registers.e);
				break;
			case 0xF4: // SET 6, H
				SET(0x06, registers.h);
				break;
			case 0xF5: // SET 6, L
				SET(0x06, registers.l);
				break;
			case 0xF6: // SET 6, (HL)
				memory.write(registers.hl.get(), SET(0x06, memory.read(registers.hl.get())));
				break;
			case 0xF7: // SET 6, A
				SET(0x06, registers.a);
				break;
			case 0xF8: // SET 7, B
				SET(0x07, registers.b);
				break;
			case 0xF9: // SET 7, C
				SET(0x07, registers.c);
				break;
			case 0xFA: // SET 7, D
				SET(0x07, registers.d);
				break;
			case 0xFB: // SET 7, E
				SET(0x07, registers.e);
				break;
			case 0xFC: // SET 7, H
				SET(0x07, registers.h);
				break;
			case 0xFD: // SET 7, L
				SET(0x07, registers.l);
				break;
			case 0xFE: // SET 7, (HL)
				memory.write(registers.hl.get(), SET(0x07, memory.read(registers.hl.get())));
				break;
			case 0xFF: // SET 7, A
				SET(0x07, registers.a);
				break;

			default: // TODO: Error Log Data Here or handle interrupt
				break;
		}
#pragma endregion
	}
}