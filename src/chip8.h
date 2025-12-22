//
// Created by yadu nandan on 10/14/25.
//

#ifndef RETRO_CONSOLE_CHIP8_H
#define RETRO_CONSOLE_CHIP8_H
#include <cstdint>

class chip8 {
    private:
        uint8_t gen_register[16];
        uint8_t memory[4096];
        uint16_t pc;
        uint16_t sp;
        uint16_t I;
        uint8_t stack[16];
        uint8_t delay_timer;
        uint8_t sound_timer;
        uint8_t display[64*32];
        char content[200];
    public:
        chip8() {
            pc = 0x200;
            sp = 0;
            I =0;
            delay_timer = 0;
            sound_timer = 0;
            for (int i =0; i<16; i++) {
                stack[i]=0;
                gen_register[i] =0;
            }
            for (int i= 0; i< 4096; i++) {
                memory[i]=0;
            }
            for (int i =0; i<64*32; i++) {
                display[i]=0;
            }
        }
    void loadRom(const char*);
    void debugPrintMemory();
    void cycle();
    void updateTimers();
    void clearDisplay();
    const uint8_t* getDisplay();
};

#endif //RETRO_CONSOLE_CHIP8_H