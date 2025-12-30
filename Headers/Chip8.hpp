#pragma once
#include <cstdint>
#include <array>
#include <stack>


class Chip8 {

    private: 
        std::array<uint8_t, 4096> memory;

        std::array<uint8_t, 16> V; // registers: V0 V1 V2 ... V9 VA VB VC VD VE VF
        uint16_t I; // Index register
        uint16_t PC; // Program Counter

        // The stack is used to store return addresses during subroutine calls
        std::stack<uint16_t> stack;

        // 8-bit which automatically decrements at 60 Hz (60 times per second) until reaching zero:
        uint8_t delayTimer; 
        uint8_t soundTimer;

        std::array<uint8_t, 64 * 32> display;

        std::array<uint8_t, 16> keys; // 16 inputs
 
    public:

    Chip8();
    void loadROM(const char* filename);
    void cycle();

    const std::array<uint8_t, 64 * 32>& getDisplay() const { return display; }
    uint16_t getPC() const { return PC; }  
    void setKey(uint8_t key, uint8_t value) { keys[key] = value; }
    void updateTimers() {
        if (delayTimer > 0) delayTimer--;
        if (soundTimer > 0) soundTimer--;
    }



};
