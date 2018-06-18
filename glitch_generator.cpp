    // Project: I2C to WishBone in SystemC
    // File: glitch_generator.cpp
    // Autor: Diego Herrera
    // ITCR 2018


#include "glitch_generator.h"

void glitch_generator::glitchLoop()
{
    int waitTime = 0;
    while(true)
    {
        
        waitTime = (rand() % MAX_FREQ);
        wait(waitTime);

        glitch_en = true;
        change = ~change;
        
        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime);
        
        
        glitch = ~glitch;
        change = ~change;

        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime);

        glitch_en = false;
        change = ~change;

    }

}

void glitch_generator::setGlitch()
{    
    sc_logic hiZ;
    hiZ = 'z';
    while(true)
    {
        
        if(glitch_en)
        {
            out.write(glitch);
        }
        else
        {
            out.write(hiZ);
        }

    }

}
