//
// Created by yadu nandan on 12/5/25.
//


#include "chip8.h"

#include <fstream>
#include <iosfwd>
#include <iostream>

// Chip-8 built-in font sprites (0-F), each character is 5 bytes
// These are loaded into memory at 0x000-0x04F during initialization
static constexpr uint8_t FONTSET[80] = {
    // 0
    0xF0, 0x90, 0x90, 0x90, 0xF0,
    // 1
    0x20, 0x60, 0x20, 0x20, 0x70,
    // 2
    0xF0, 0x10, 0xF0, 0x80, 0xF0,
    // 3
    0xF0, 0x10, 0xF0, 0x10, 0xF0,
    // 4
    0x90, 0x90, 0xF0, 0x10, 0x10,
    // 5
    0xF0, 0x80, 0xF0, 0x10, 0xF0,
    // 6
    0xF0, 0x80, 0xF0, 0x90, 0xF0,
    // 7
    0xF0, 0x10, 0x20, 0x40, 0x40,
    // 8
    0XF0, 0x90, 0xF0, 0x90, 0xF0,
    // 9
    0xF0, 0x90, 0xF0, 0x10, 0xF0,
    // A
    0xF0, 0x90, 0xF0, 0x90, 0x90,
    // B
    0xE0, 0x90, 0xE0, 0x90, 0xE0,
    // C
    0xF0, 0x80, 0x80, 0x80, 0xF0,
    // D
    0xE0, 0x90, 0x90, 0x90, 0xE0,
    // E
    0xF0, 0x80, 0xF0, 0x80, 0xF0,
    // F
    0xF0, 0x80, 0xF0, 0x80, 0x80,
};


void chip8::loadRom(const char* fileName) {
    std::ifstream asset;
    asset.open(fileName, std::ios::in | std::ios::binary);
    if (asset.is_open()) {
        asset.seekg(0,std::ifstream::end);
        int size = asset.tellg();
        asset.seekg(0,std::ifstream::beg);
        asset.read(reinterpret_cast<char*>(memory)+0x200,size);
        asset.close();
    }else {
        std::cout<<"Failed to open file:"<< fileName<<std::endl;
    }
    for (int i= 0; i < static_cast<int>(std::size(FONTSET)); i++) {
        memory[i] = FONTSET[i];
    }
}

void chip8::updateTimers() {
    delay_timer--;
    if (sound_timer >0) {
        sound_timer--;
    }
}


const uint8_t* chip8::getDisplay() {
    return display;
}

void chip8::cycle() {
    uint8_t msb,lsb;
    msb = memory[pc];
    lsb = memory[pc+1];
    uint16_t ins = msb<<8|lsb;
    std::cout<< std::hex << (int)ins << std::endl;
    uint16_t fn = (ins >> 12) & 0x0F ;
    switch (fn) {
        case 0x0: // clear display
            if (ins == 0x00E0) {
                clearDisplay();
            }
            break;
        case 0x1: { // jump to address
            uint16_t addr = ins & 0xFFF;
            pc = addr;
            pc-=2;
        }
            break;
        case 0x6: // set operation
        {
            const int reg = (ins >> 8) & 0x0F;
            uint8_t v = ins & 0xFF;
            gen_register[reg] = v;
        }
            break;
        case 0xA: {
            uint16_t v = ins & 0xFFF;
            I = v;
        }
            break;
        case 0x7: {
            const int reg = (ins >> 8) & 0x0F;
            uint8_t v = ins & 0xFF;
            gen_register[reg]+=v;
        }
            break;
        case 0xD: {
            gen_register[0xF] = 0;
            uint8_t X = (ins >> 8) & 0x0F;
            uint8_t Y = (ins >> 4) & 0x0F;
            uint8_t N = ins & 0x0F;
            uint8_t x = gen_register[X];
            uint8_t y = gen_register[Y];
            for (int row=0; row<N;row++) {
                uint8_t sprt = memory[I+row];
                for (int bit=0; bit<8; bit++) {
                    if (sprt & (0x80 >> bit)) {
                        int px = (x + bit) % 64;
                        int py = (y + row) % 32;
                        int loc = py*64 +px;
                        if (display[loc]== 1) {
                            gen_register[0xF] =1;
                        }
                        display[loc] ^=1;
                    }
                }
            }
        }
        break;
    }
    pc+=2;
}

void chip8::clearDisplay() {
    for (uint8_t & ele : display) {
        ele=0;
    }
}

void chip8::debugPrintMemory() {
    unsigned long i =0;
    while (i<10 && (0x200+i < (sizeof memory/ sizeof(uint8_t)))) {
        std::cout<<std::hex<<(int)memory[0x200+i]<<" ";
        i++;
    }
    std::cout << std::endl;
}