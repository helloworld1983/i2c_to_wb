    // Project: I2C to WishBone in SystemC
    // File: glitch_generator.cpp
    // Autor: Diego Herrera
    // ITCR 2018


#include "glitch_generator.h"

void glitch_generator::glitchLoop()
{
    int waitTime = 0;
    sc_logic glitch;
    glitch = 'z';

    while(true)
    {        
        waitTime = (rand() % MAX_FREQ);
        wait(waitTime,SC_NS);
        out.write(glitch);

        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime,SC_NS);
        glitch = '1';
        out.write(glitch);
  
        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime,SC_NS);
        glitch = 'z';
        out.write(glitch);      
    }
}
