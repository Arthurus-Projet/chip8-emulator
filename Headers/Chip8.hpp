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

        std::stack<uint16_t> stack;

        // 8-bit which automatically decrements at 60 Hz (60 times per second) until reaching zero:
        uint8_t delayTimer; 
        uint8_t soundTimer;

        std::array<uint8_t, 64 * 32> display;

        std::array<uint8_t, 16> keys; // 16 inputs

        





};
