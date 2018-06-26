    // Project: I2C to WishBone in SystemC
    // File: wb_slave_model.h 
    // Autor: Diego Herrera
    // ITCR 2018

#ifndef _WB_SLAVE_MODEL_H
#define _WB_SLAVE_MODEL_H

#include <systemc.h>
#include <stdlib.h>
#include <iostream>
#include <fstream> // To use ifstream
#include <vector>

#define DWIDTH 32
#define AWIDTH 8
#define ACK_DELAY 2
#define SLAVE_RAM_INIT "Model/wb_slave_32_bit.txt"


SC_MODULE(wb_slave_model)
{
    // channels
    sc_in<bool>                 clk_i;
    sc_in<bool>                 rst_i;
    sc_out<sc_bv<(DWIDTH)> >  dat_o;
    sc_in<sc_bv<(DWIDTH)> >   dat_i;
    sc_in<sc_bv<(AWIDTH)> >   adr_i;
    sc_in<bool>                 cyc_i;
    sc_in<bool>                 stb_i;
    sc_in<bool>                 we_i;
    sc_in<sc_bv<DWIDTH/8> > sel_i;
    sc_out<bool>                ack_o;
    sc_out<bool>                err_o;
    sc_out<bool>                rty_o;

    std::vector<uint> ram;  

    void tracing(sc_trace_file *tf); 

    void ackDelayed();
    void dataGen();
    void readMemory(); 
    void setOutData();

    SC_CTOR(wb_slave_model)
    {
        readMemory();

        SC_THREAD(ackDelayed);
            sensitive << clk_i;
            sensitive << stb_i;
            sensitive << cyc_i;

        SC_THREAD(dataGen);
            sensitive << clk_i.pos();

        SC_METHOD(setOutData);
            sensitive << clk_i;

    }

}; // end class wb_slave_model

#endif