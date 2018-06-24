    // Project: I2C to WishBone in SystemC
    // File: wb_slave_model.h 
    // Autor: Diego Herrera
    // ITCR 2018

#ifndef _TB_DUT_H
#define _TB_DUT_H

#include <systemc.h>




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