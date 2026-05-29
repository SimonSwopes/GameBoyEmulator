#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace Cart
{
    class Cartridge
    {
    public:
        bool loadFromFile(const std::string& path);

        uint8_t read(uint16_t address) const;
        std::string getTitle() const;
        uint8_t getType() const;

    private:
        std::vector<uint8_t> data;

        bool validateChecksum() const;
    };
}
