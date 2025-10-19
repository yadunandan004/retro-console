//
// Created by yadu nandan on 10/14/25.
//

#ifndef RETRO_CONSOLE_CHIP8_H
#define RETRO_CONSOLE_CHIP8_H
#include <cstdint>

class chip8 {
    private:
        uint8_t v_register[16];
    public:
        chip8(){
            for (int i =0; i < sizeof(v_register)/sizeof(v_register[0]); i++){
                v_register[i]=0;
            }
        }

};

#endif //RETRO_CONSOLE_CHIP8_H