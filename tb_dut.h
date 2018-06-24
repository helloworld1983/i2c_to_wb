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
    
    SC_CTOR(tb_dut)
    {

    }

}; // end class tb_dut

#endif