#include "RegisterFile.h"

namespace CPU {
    // 16 bit setters
    void RegisterFile::setAF(uint16_t value) {
        a.set((value & 0xFF00) >> 8);
        f.set(value & 0xF0); // Only the higher 4 bits are set, lower 4 bits are zero
    }

    void RegisterFile::setBC(uint16_t value) {
        b.set((value & 0xFF00) >> 8);
        c.set(value & 0x00FF);
    }

    void RegisterFile::setDE(uint16_t value) {
        d.set((value & 0xFF00) >> 8);
        e.set(value & 0x00FF);
    }

    void RegisterFile::setHL(uint16_t value) {
        h.set((value & 0xFF00) >> 8);
        l.set(value & 0x00FF);
    }

    // Flag Setters
    void RegisterFile::setZeroFlag(bool value) { setF(0x80, value); }
    void RegisterFile::setSubtractionFlag(bool value) { setF(0x40, value); }
    void RegisterFile::setHalfCarryFlag(bool value) { setF(0x20, value); }
    void RegisterFile::setCarryFlag(bool value) { setF(0x10, value); }

    void RegisterFile::setF(uint8_t mask, bool value)
    {
		uint8_t fValue = f.get();
		fValue = value ? fValue | mask : fValue & ~mask;
		f.set(fValue);
    }
}