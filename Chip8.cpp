#include "Headers/Chip8.hpp"
#include <fstream>
#include <iostream>
#include <vector>






Chip8::Chip8() {
    PC = 0x200; // ROMs start at 0x200.
    I = 0;
    delayTimer = 0;
    soundTimer = 0;
    memory.fill(0);
    V.fill(0);
    display.fill(0);
    keys.fill(0);

    // built-in CHIP-8 typeface, defined in the original 1970s specification. 
    // All CHIP-8 emulators must load it.
    const std::array<uint8_t, 80> fontset = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    /* 
    0xF0 = 11110000 = ####
    0x90 = 10010000 = #  #
    0x90 = 10010000 = #  #
    0x90 = 10010000 = #  #
    0xF0 = 11110000 = ####

    0x20 = 00100000 =   #
    0x60 = 01100000 =  ##
    0x20 = 00100000 =   #
    0x20 = 00100000 =   #
    0x70 = 01110000 =  ###
    */
    
    std::copy(fontset.begin(), fontset.end(), memory.begin() + 0x50);
    // 0x50 = 80  ==>  memory[80] = 0xF0


    




    }



void Chip8::loadROM(const char* filename) {


    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Opening error \n";
        return;
    }

    std::vector<uint8_t> buffer(
        std::istreambuf_iterator<char>(file), 
        {}
    );

    if (buffer.size() > 3584) {
        std::cerr << "ROM too big ! \n";
        return;
        }

    std::copy(buffer.begin(), buffer.end(), memory.begin() + 0x200);
    
    file.close();
}

void Chip8::cycle() {

    uint16_t opcode = (memory[PC] << 8 | memory[PC + 1]);
    PC += 2;

/* 
    ---------------------------------------
    | X for what register use (4 bits)    |
    | Y seond register (4 bits)           |
    | N can be a sprite heights (4 bits)  |
    | NN value (1 byte)                   |
    | NNN memory adress (12 bits)         |
    ---------------------------------------
*/

    uint8_t X = (opcode >> 8) & 0xF;
    uint8_t Y = (opcode >> 4) & 0xF;
    uint8_t N = opcode & 0xF;  // 0xF = 15 = 1111
    uint8_t NN = opcode & 0xFF; // 0xFF = 255 = 1111 1111
    uint16_t NNN = opcode & 0xFFF; // 0xFFF = 4095 = 1111 1111 1111

    switch (opcode & 0xF000) {  // first nibble (instruction type)
    case 0x0000:
        // 00E0 and 00EE
        if (opcode == 0x00E0) {
            display.fill(0);
        } else 
            if (opcode == 0x00EE) {
                PC =  stack.top();
                stack.pop();
            }

        break;
    case 0x1000:     
        PC = NNN;
        break;
    case 0x6000:
        V[X] = NN;
        break;
   
    case 0x7000:
        V[X] += NN;  
        break;
    case 0x2000:
        stack.push(PC);
        PC = NNN;
        break;
    case 0x3000:
        if (V[X] == NN)
            PC += 2;
        break;
    case 0x4000:
        if (V[X] != NN) 
            PC += 2;
        break;
    case 0xA000:
        I = NNN;
        break;
     }

}


