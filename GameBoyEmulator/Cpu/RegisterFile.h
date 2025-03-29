#include "Register.h"

#pragma once

namespace CPU {
	class RegisterFile
	{
		public:
			Register_unint8 a, b, c, d, f, e, h, l;
			Register_uint16 af, bc, de, hl, sp, pc;

			RegisterFile() : a(), b(), c(), d(), e(), h(), l(), f(), pcHigh(), pcLow(),
				spHigh(), spLow(), bc(b, c), de(d, e), hl(h, l), af(a, f), pc(pcHigh, pcLow), sp(spHigh, spLow) {}

			// Setters
			void setA(uint8_t value) { a.set(value); }
			void setB(uint8_t value) { b.set(value); }
			void setC(uint8_t value) { c.set(value); }
			void setD(uint8_t value) { d.set(value); }
			void setE(uint8_t value) { e.set(value); }
			void setH(uint8_t value) { h.set(value); }
			void setL(uint8_t value) { l.set(value); }

			void setAF(uint16_t value) { af.set(value); }
			void setBC(uint16_t value) { bc.set(value); }
			void setDE(uint16_t value) { de.set(value); }
			void setHL(uint16_t value) { hl.set(value); }
			void setSP(uint16_t value) { sp.set(value); }

			// F register lower 4 bits are always 0
			void setZeroFlag(bool value) { setF(0x80, value); }
			void setSubtractionFlag(bool value) { setF(0x40, value); }
			void setHalfCarryFlag(bool value) { setF(0x20, value); }
			void setCarryFlag(bool value) { setF(0x10, value); }

			// Getters
			uint8_t getA() const { return a.get(); }
			uint8_t getB() const { return b.get(); }
			uint8_t getC() const { return c.get(); }
			uint8_t getD() const { return d.get(); }
			uint8_t getE() const { return e.get(); }
			uint8_t getF() const { return f.get(); }
			uint8_t getH() const { return h.get(); }
			uint8_t getL() const { return l.get(); }

			uint16_t getAF() const { return af.get(); }
			uint16_t getBC() const { return bc.get(); }
			uint16_t getDE() const { return de.get(); }
			uint16_t getHL() const { return hl.get(); }
			uint16_t getSP() const { return sp.get(); }

			// Flag Getters
			bool getZeroFlag() const { return f.get() & 0x80; }
			bool getSubtractionFlag() const { return f.get() & 0x40; }
			bool getHalfCarryFlag() const { return f.get() & 0x20; }
			bool getCarryFlag() const { return f.get() & 0x10; }

		private:
			Register_unint8 pcHigh, pcLow, spHigh, spLow;
			void setF(uint8_t mask, bool value);

	};
}