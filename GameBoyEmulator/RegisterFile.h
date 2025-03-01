#include "Register.h"

#pragma once

namespace CPU {
	class RegisterFile
	{
		private:
			ArithmeticTargetRegister a, b, c, d, e, h, l;
			Register f;

		public:
			RegisterFile() : a(), b(), c(), d(), e(), f(), h(), l() {}

			// Setters
			void setA(uint8_t value) { a.set(value); }
			void setB(uint8_t value) { b.set(value); }
			void setC(uint8_t value) { c.set(value); }
			void setD(uint8_t value) { d.set(value); }
			void setE(uint8_t value) { e.set(value); }
			void setH(uint8_t value) { h.set(value); }
			void setL(uint8_t value) { l.set(value); }

			void setAF(uint16_t value);
			void setBC(uint16_t value);
			void setDE(uint16_t value);
			void setHL(uint16_t value);

			// F register lower 4 bits are always 0
			void setZeroFlag(bool value);
			void setSubtractionFlag(bool value);
			void setHalfCarryFlag(bool value);
			void setCarryFlag(bool value);

			// Getters
			uint8_t getA() const { return a.get(); }
			uint8_t getB() const { return b.get(); }
			uint8_t getC() const { return c.get(); }
			uint8_t getD() const { return d.get(); }
			uint8_t getE() const { return e.get(); }
			uint8_t getF() const { return f.get(); }
			uint8_t getH() const { return h.get(); }
			uint8_t getL() const { return l.get(); }

			uint16_t getAF() const { return (a.get() << 8) | f.get(); }
			uint16_t getBC() const { return (b.get() << 8) | c.get(); }
			uint16_t getDE() const { return (d.get() << 8) | e.get(); }
			uint16_t getHL() const { return (h.get() << 8) | l.get(); }

			// Flag Getters
			bool getZeroFlag() const { return f.get() & 0x80; }
			bool getSubtractionFlag() const { return f.get() & 0x40; }
			bool getHalfCarryFlag() const { return f.get() & 0x20; }
			bool getCarryFlag() const { return f.get() & 0x10; }

		private:
			void setF(uint8_t mask, bool value);
	};
}