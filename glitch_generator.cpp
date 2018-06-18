    // Project: I2C to WishBone in SystemC
    // File: glitch_generator.cpp
    // Autor: Diego Herrera
    // ITCR 2018


#include "glitch_generator.h"

void glitch_generator::glitchLoop()
{
    int waitTime = 0;
    sc_logic hiZ;
    hiZ = 'z';
    cout << "First Loop" << endl;
    while(true)
    {        
        cout << "Inside" << endl;
        waitTime = (rand() % MAX_FREQ);
        wait(waitTime,SC_NS);

        cout << "Time" << waitTime << endl;

        glitch_en = true;
      
        out.write(glitch);

        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime,SC_NS);
        
        
        glitch = '1';
    
        out.write(glitch);
  
        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime,SC_NS);
        glitch_en = false;
        
        out.write(hiZ);      

    }

}

void glitch_generator::setGlitch()
{    
    // int test = 1000000;
    // sc_logic hiZ;

    // hiZ = 'z';
    // while(test>0)
    // {        
        // if(glitch_en)
        // {
        //     out.write(glitch);
        // }
        // else
        // {
        //     out.write(hiZ);
        // }
    //     test--;
    // }

}
