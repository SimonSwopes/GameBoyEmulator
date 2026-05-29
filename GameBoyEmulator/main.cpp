#include <iostream>
#include "Cartridge/Cartridge.h"
#include "Cpu/ControlUnit.h"

int main()
{
    // TODO: replace with UI file picker
    const std::string romPath = "C:/path/to/rom.gb";

    Cart::Cartridge cartridge;
    if (!cartridge.loadFromFile(romPath))
        return 1;

    CPU::ControlUnit cpu;
    cpu.loadCartridge(cartridge);
    cpu.reset();

    while (true)
    {
        cpu.cycle();
    }
}
