    // Project: I2C to WishBone in SystemC
    // File: glitch_generator.h 
    // Autor: Diego Herrera
    // ITCR 2018

#ifndef _GLITCH_GENERATOR_H
#define _GLITCH_GENERATOR_H

#include <systemc.h>
#include <stdlib.h>

#define ENABLE 0
#define MAX_FREQ 10000
#define MAX_WIDTH 120

SC_MODULE(glitch_generator)
{
  // channels
    sc_out<sc_logic> in;
    sc_out<sc_logic> out;

    sc_bit glitch_generator_en;
    sc_logic glitch;
    bool glitch_en;
    sc_signal<bool> change;

    void glitchLoop();   
    void setGlitch(); 

     SC_HAS_PROCESS(glitch_generator);
    // constructor
    glitch_generator(sc_module_name name_):
    sc_module(name_)
    {
        SC_THREAD(glitchLoop);
        sensitive << in;

        SC_THREAD(setGlitch);
        sensitive << change;
    }

}; // end class glitch_generator

#endif