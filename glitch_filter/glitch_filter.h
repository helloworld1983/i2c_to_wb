#ifndef GLITCH_FILTER_H
#define GLITCH_FILTER_H

#include "systemc.h"

#define SIZE 3

SC_MODULE (glitchFilter)
{
    // -----------------------------------------> Module Definition
    // Inputs
    sc_in_clk       clk;
    sc_in<bool>     in;
    // Outputs
    sc_out<bool>    out;
    sc_out<bool>    rise;
    sc_out<bool>    fall;

    // -----------------------------------------> Variables
    sc_bv<1>    in_reg;
    sc_bv<SIZE> buffer;
    sc_bv<4>    all_hi;
    sc_bv<4>    all_low;
    sc_bv<1>    all_hi_lsb;
    sc_bv<1>    all_low_lsb;
    sc_bv<1>    out_en;
    sc_bv<1>    temp_bit;

    // -----------------------------------------> Methods
    void tracing(sc_trace_file *tf);
    void inSyncFlop(void);
    void filter(void);
    void outputEnableToBuffer(void);
    void fallAndRise(void);

    // -----------------------------------------> Constructor
    SC_CTOR(glitchFilter)
    {
        SC_METHOD(inSyncFlop);
            sensitive << clk.pos();
        SC_METHOD(filter);
            sensitive << clk.pos();
        SC_METHOD(outputEnableToBuffer);
            sensitive << clk.pos();
        SC_METHOD(fallAndRise);
            sensitive << clk;
            sensitive << out;
    }

};  // End of Module

#endif

