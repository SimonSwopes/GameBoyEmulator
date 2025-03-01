#include <cstdint>

#pragma once
namespace CPU
{
	class Register
	{
		public:
			Register() : value(0) {}
			void set(uint8_t value) { this -> value = value; }
			uint8_t get() const { return value; }

		private:
			uint8_t value;
	};

	class ArithmeticTargetRegister : Register
	{
		public:
			ArithmeticTargetRegister() : Register() {}
			void set(uint8_t value) { Register::set(value); }
			uint8_t get() const { return Register::get(); }
	};
}