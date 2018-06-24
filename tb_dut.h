    // Project: I2C to WishBone in SystemC
    // File: wb_slave_model.h 
    // Autor: Diego Herrera
    // ITCR 2018

#ifndef _TB_DUT_H
#define _TB_DUT_H

#include <systemc.h>
#include "Model/i2c_master_model.h"
#include "Model/glitch_generator.h"
#include "Model/wb_slave_model.h"

SC_MODULE(tb_dut)
{
    // channels
    sc_in<bool>                 tb_clk;
    sc_in<bool>                 tb_rst;
    
    // Ports

    // Glitch Generator
    sc_signal<sc_logic> glitch_in;

    // i2c_master
    sc_signal<sc_logic>         i2c_clk;
    sc_signal<sc_logic>         i2c_data;
    sc_signal< sc_bv<8> >   task_write_byte_arg;
    sc_signal<bool>         task_write_byte_trigger;
    sc_signal<int>          task_read_byte_arg;
    sc_signal<bool>         task_read_byte_trigger;
    sc_signal<bool>         task_start_trigger;
    sc_signal<bool>         task_stop_trigger;

    // i2c_wb_slave
    sc_signal<bool>                 clk_i;
    sc_signal<bool>                 rst_i;
    sc_signal<sc_uint<(DWIDTH)> >   dat_o;
    sc_signal<sc_uint<(DWIDTH)> >   dat_i;
    sc_signal<sc_uint<(AWIDTH)> >   adr_i;
    sc_signal<bool>                 cyc_i;
    sc_signal<bool>                 stb_i;
    sc_signal<bool>                 we_i;
    sc_signal<sc_uint<(DWIDTH)/8> > sel_i;
    sc_signal<bool>                 ack_o;
    sc_signal<bool>                 err_o;
    sc_signal<bool>                 rty_o;

    // Connect the DUT

    SC_CTOR(tb_dut)
    {
        // i2c_master_model
        i2c_master_model i2c_master_model_tb("i2c_master_model");
        i2c_master_model_tb.i2c_clk(i2c_clk.to_bool());
        i2c_master_model_tb.i2c_data(i2c_data.to_bool());
        i2c_master_model_tb.task_write_byte_arg(task_write_byte_arg);
        i2c_master_model_tb.task_write_byte_trigger(task_write_byte_trigger);
        i2c_master_model_tb.task_read_byte_arg(task_read_byte_arg);
        i2c_master_model_tb.task_read_byte_trigger(task_read_byte_trigger);
        i2c_master_model_tb.task_start_trigger(task_start_trigger);
        i2c_master_model_tb.task_stop_trigger(task_stop_trigger);

        // i2c_wb_slave
        wb_slave_model wbSlaveModel("wbSlaveModel");
        wbSlaveModel.clk_i(tb_clk);
        wbSlaveModel.rst_i(tb_rst);
        wbSlaveModel.dat_o(dat_o);
        wbSlaveModel.dat_i(dat_i);
        wbSlaveModel.adr_i(adr_i);
        wbSlaveModel.cyc_i(cyc_i);
        wbSlaveModel.stb_i(stb_i);
        wbSlaveModel.we_i(we_i);
        wbSlaveModel.sel_i(sel_i);
        wbSlaveModel.ack_o(ack_o);
        wbSlaveModel.err_o(err_o);
        wbSlaveModel.rty_o(rty_o);

        // glitch_generator
        glitch_generator glitchGen("glitchGen");
        glitchGen.glitch(glitch_in);
    }

}; // end class tb_dut

#endif