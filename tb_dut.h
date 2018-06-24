    // Project: I2C to WishBone in SystemC
    // File: wb_slave_model.h 
    // Autor: Diego Herrera
    // ITCR 2018

#ifndef _TB_DUT_H
#define _TB_DUT_H

#include <systemc.h>
#include <stdlib.h>
#include <iostream>
#include <fstream> // To use ifstream
#include <vector>

#define DWIDTH 32
#define AWIDTH 8
#define ACK_DELAY 2
#define SLAVE_RAM_INIT "Model/wb_slave_32_bit.txt"


SC_MODULE(tb_dut)
{
    // channels
    sc_in<bool>                 tb_clk;
    sc_in<bool>                 tb_rst;
    

    std::vector<uint> ram;   

    void ackDelayed();
    void dataGen();
    void readMemory(); 
    void setOutData();

    SC_CTOR(tb_dut)
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

}; // end class tb_dut

#endif