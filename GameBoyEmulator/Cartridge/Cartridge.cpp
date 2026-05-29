#include "Cartridge.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace Cart
{
    bool Cartridge::loadFromFile(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file.is_open())
        {
            std::cerr << "Failed to open ROM: " << path << "\n";
            return false;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        data.resize(static_cast<size_t>(size));
        if (!file.read(reinterpret_cast<char*>(data.data()), size))
        {
            std::cerr << "Failed to read ROM: " << path << "\n";
            return false;
        }

        if (data.size() < 0x0150)
        {
            std::cerr << "ROM too small to be a valid Game Boy cartridge\n";
            return false;
        }

        if (!validateChecksum())
        {
            std::cerr << "ROM header checksum invalid\n";
            return false;
        }

        std::cout << "Loaded ROM: " << getTitle()
                  << "  type=0x" << std::hex << static_cast<int>(getType())
                  << "  size=" << std::dec << data.size() << " bytes\n";
        return true;
    }

    uint8_t Cartridge::read(uint16_t address) const
    {
        if (address < data.size())
            return data[address];
        return 0xFF;
    }

    std::string Cartridge::getTitle() const
    {
        // 0x0134-0x0143: game title, ASCII, null-padded
        std::string title(reinterpret_cast<const char*>(&data[0x0134]), 16);
        title.erase(std::find(title.begin(), title.end(), '\0'), title.end());
        return title;
    }

    uint8_t Cartridge::getType() const
    {
        return data[0x0147];
    }

    bool Cartridge::validateChecksum() const
    {
        // Standard GB header checksum over 0x0134-0x014C
        uint8_t checksum = 0;
        for (uint16_t addr = 0x0134; addr <= 0x014C; ++addr)
            checksum = checksum - data[addr] - 1;
        return checksum == data[0x014D];
    }
}
