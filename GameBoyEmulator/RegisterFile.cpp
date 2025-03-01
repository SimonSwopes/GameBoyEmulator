#include "RegisterFile.h"

namespace CPU {
    // 16 bit setters
    void RegisterFile::setAF(uint16_t value) {
        a = (value & 0xFF00) >> 8;
        f = value & 0xF0; // Only the higher 4 bits are set, lower 4 bits are zero
    }

    void RegisterFile::setBC(uint16_t value) {
        b = (value & 0xFF00) >> 8;
        c = value & 0x00FF;
    }

    void RegisterFile::setDE(uint16_t value) {
        d = (value & 0xFF00) >> 8;
        e = value & 0x00FF;
    }

    void RegisterFile::setHL(uint16_t value) {
        h = (value & 0xFF00) >> 8;
        l = value & 0x00FF;
    }

    // Flag Setters
    void RegisterFile::setZeroFlag(bool value) { setF(0x80, value); }
    void RegisterFile::setSubtractionFlag(bool value) { setF(0x40, value); }
    void RegisterFile::setHalfCarryFlag(bool value) { setF(0x20, value); }
    void RegisterFile::setCarryFlag(bool value) { setF(0x10, value); }

    void RegisterFile::setF(uint8_t mask, bool value) {
        if (value)
            f |= mask;
        else
            f &= ~mask;
    }
}