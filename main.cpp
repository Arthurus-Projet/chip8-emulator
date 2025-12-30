#include <SFML/Graphics.hpp>
#include <bitset>
#include <iostream>
#include "Headers/Chip8.hpp"


int main() {

    Chip8 chip8;

    std::cout << "start" << std::endl;

    //chip8.loadROM("roms/danm8ku.ch8");
    //chip8.loadROM("roms/2-ibm-logo.ch8");
    chip8.loadROM("roms/Airplane.ch8");


    

    const int SCALE = 10;

    sf::RenderWindow window(sf::VideoMode(64 * SCALE, 32 * SCALE), "Chip8 Emulator");
    window.setFramerateLimit(60); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < 16; i++) {
            chip8.setKey(i, 0);
        }

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) chip8.setKey(0x1, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) chip8.setKey(0x2, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) chip8.setKey(0x3, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) chip8.setKey(0xC, 1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) chip8.setKey(0x4, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) chip8.setKey(0x5, 1);  // Z AZERTY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) chip8.setKey(0x6, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) chip8.setKey(0xD, 1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) chip8.setKey(0x7, 1);  // Q AZERTY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) chip8.setKey(0x8, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) chip8.setKey(0x9, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) chip8.setKey(0xE, 1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) chip8.setKey(0xA, 1);  // W AZERTY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) chip8.setKey(0x0, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) chip8.setKey(0xB, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) chip8.setKey(0xF, 1);

        for (int i = 0; i < 7; i++) {
            chip8.cycle();
        }

        chip8.updateTimers();

        
        static int frameCount = 0;
        if (frameCount++ % 60 == 0) {  
            std::cout << "PC: 0x" << std::hex << chip8.getPC() << std::endl;
        }

        window.clear(sf::Color::Black);


        const auto& display = chip8.getDisplay();

        for (int x = 0; x < 64; ++x) {
            for (int y = 0; y < 32; ++y) {
                if (display[64 * y + x] == 1) {
                    sf::RectangleShape pixel(sf::Vector2f(SCALE, SCALE));
                    pixel.setPosition(x * SCALE, y * SCALE);
                    pixel.setFillColor(sf::Color::White);
                    window.draw(pixel);
                }

            }
        }



        window.display();

    }


    return 0;
}

