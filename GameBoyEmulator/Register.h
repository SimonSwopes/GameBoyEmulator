#include <cstdint>

#pragma once
namespace CPU
{
	class Register_unint8
	{
		public:
			Register_unint8() : value(0) {}
			void set(uint8_t value) { this -> value = value; }
			uint8_t get() const { return value; }

		private:
			uint8_t value;
	};

	class ArithmeticTargetRegister_unint8 : Register_unint8
	{
		public:
			ArithmeticTargetRegister_unint8() : Register_unint8() {}
			void set(uint8_t value) { Register_unint8::set(value); }
			uint8_t get() const { return Register_unint8::get(); }
	};

	class Register_uint16
	{
		public:
			Register_uint16(Register_unint8& high, Register_unint8& low) : high(high), low(low) {}
			void set(uint16_t value) { high.set((value & 0xFF00) >> 8); low.set(value & 0x00FF); }
			uint16_t get() const { return (high.get() << 8) | low.get(); }

		protected:
			Register_unint8& high;
			Register_unint8& low;
	};

	class ArithmeticTargetRegister_unint16 : Register_uint16
	{
		public:
			ArithmeticTargetRegister_unint16(Register_unint8& high, Register_unint8& low) : Register_uint16(high, low) {}
			void set(uint16_t value) { Register_uint16::set(value); }
			uint16_t get() const { return Register_uint16::get(); }
	};
}