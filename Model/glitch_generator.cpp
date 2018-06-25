    // Project: I2C to WishBone in SystemC
    // File: glitch_generator.cpp
    // Autor: Diego Herrera
    // ITCR 2018


#include "glitch_generator.h"

void glitch_generator::glitchLoop()
{
    int waitTime = 0;
    sc_logic glitchGen;
    glitchGen = 'z';

    while(true)
    {        
        glitchGen = '0';
        waitTime = (rand() % MAX_FREQ);
        wait(waitTime,SC_NS);
        glitch.write(glitchGen);

        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime,SC_NS);
        glitchGen = '1';
        glitch.write(glitchGen);
  
        waitTime = (rand() % MAX_WIDTH);
        wait(waitTime,SC_NS);
        glitchGen = 'z';
        glitch.write(glitchGen);      
    }
}

void glitch_generator::tracing(sc_trace_file *tf)
{
    cout << "INVOKED - "<< "tracing" << endl;
    const std::string str = this->name();
    
    // Dump local signals
    sc_trace(tf, this->glitch, str+".glitch");
}
