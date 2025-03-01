#include <cstdint>

#pragma once

namespace CPU {
	class RegisterFile
	{
	private:
		uint8_t a, b, c, d, e, f, h, l;

	public:
		RegisterFile() : a(0), b(0), c(0), d(0), e(0), f(0), h(0), l(0) {}

		// Setters
		void setA(uint8_t value) { a = value; }
		void setB(uint8_t value) { b = value; }
		void setC(uint8_t value) { c = value; }
		void setD(uint8_t value) { d = value; }
		void setE(uint8_t value) { e = value; }
		void setH(uint8_t value) { h = value; }
		void setL(uint8_t value) { l = value; }

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
		uint8_t getA() const { return a; }
		uint8_t getB() const { return b; }
		uint8_t getC() const { return c; }
		uint8_t getD() const { return d; }
		uint8_t getE() const { return e; }
		uint8_t getH() const { return h; }
		uint8_t getL() const { return l; }

		uint16_t getAF() const { return (a << 8) | f; }
		uint16_t getBC() const { return (b << 8) | c; }
		uint16_t getDE() const { return (d << 8) | e; }
		uint16_t getHL() const { return (h << 8) | l; }

	private:
		void setF(uint8_t mask, bool value);
	};
}