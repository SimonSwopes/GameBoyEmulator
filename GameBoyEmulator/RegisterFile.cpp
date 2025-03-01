#include "RegisterFile.h"

namespace CPU {
    void RegisterFile::setF(uint8_t mask, bool value)
    {
		uint8_t fValue = f.get();
		fValue = value ? fValue | mask : fValue & ~mask;
		f.set(fValue);
    }
}