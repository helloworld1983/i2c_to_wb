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
#include "i2c_to_wb_top.h"

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

    sc_signal<bool>             i2c_clk_b;
    sc_signal<bool>             i2c_data_b;

    sc_signal< sc_bv<8> >       task_write_byte_arg;
    sc_signal<bool>             task_write_byte_trigger;
    sc_signal<int>              task_read_byte_arg;
    sc_signal<bool>             task_read_byte_trigger;
    sc_signal<bool>             task_start_trigger;
    sc_signal<bool>             task_stop_trigger;

    sc_signal<bool>             i2c_data_in;
    sc_signal<bool>             i2c_clk_in;
    sc_signal<bool>             i2c_data_out;
    sc_signal<bool>             i2c_clk_out;
    sc_signal<bool>             i2c_data_oe;
    sc_signal<bool>             i2c_clk_oe;

    sc_signal< sc_bv<32> >    wb_data_i;
    sc_signal< sc_bv<32> >    wb_data_o;
    sc_signal< sc_bv<8> >     wb_addr_o;
    sc_signal< sc_bv<4> >       wb_sel_o;
    sc_signal<bool>             wb_we_o;
    sc_signal<bool>             wb_cyc_o;
    sc_signal<bool>             wb_stb_o;
    sc_signal<bool>             wb_ack_i;
    sc_signal<bool>             wb_err_i;
    sc_signal<bool>             wb_rty_i;

    SC_CTOR(tb_dut)
    {
        SC_METHOD(clockCast);
            sensitive << i2c_clk;
            sensitive << i2c_data;

        // i2c_master_model
        i2c_master_model i2cMasterModel("i2c_master_model");
        i2cMasterModel.i2c_clk(i2c_clk_b);
        i2cMasterModel.i2c_data(i2c_data_b);
        i2cMasterModel.task_write_byte_arg(task_write_byte_arg);
        i2cMasterModel.task_write_byte_trigger(task_write_byte_trigger);
        i2cMasterModel.task_read_byte_arg(task_read_byte_arg);
        i2cMasterModel.task_read_byte_trigger(task_read_byte_trigger);
        i2cMasterModel.task_start_trigger(task_start_trigger);
        i2cMasterModel.task_stop_trigger(task_stop_trigger);

        // i2c_wb_top
        i2c_to_wb_top i2cWbTop("i2cWbTop");
        i2cWbTop.i2c_data_in(i2c_data_in);
        i2cWbTop.i2c_clk_in(i2c_clk_in);
        i2cWbTop.i2c_data_out(i2c_data_out);
        i2cWbTop.i2c_clk_out(i2c_clk_out);
        i2cWbTop.i2c_data_oe(i2c_data_oe);
        i2cWbTop.i2c_clk_oe(i2c_clk_oe);
        i2cWbTop.wb_data_i(wb_data_i);
        i2cWbTop.wb_data_o(wb_data_o);
        i2cWbTop.wb_addr_o(wb_addr_o);
        i2cWbTop.wb_sel_o(wb_sel_o);
        i2cWbTop.wb_we_o(wb_we_o);
        i2cWbTop.wb_cyc_o(wb_cyc_o);
        i2cWbTop.wb_stb_o(wb_stb_o);
        i2cWbTop.wb_ack_i(wb_ack_i);
        i2cWbTop.wb_err_i(wb_err_i);
        i2cWbTop.wb_rty_i(wb_rty_i);
        i2cWbTop.wb_clk_i(tb_clk);
        i2cWbTop.wb_rst_i(tb_rst);


        // i2c_wb_slave
        wb_slave_model wbSlaveModel("wbSlaveModel");
        wbSlaveModel.clk_i(tb_clk);
        wbSlaveModel.rst_i(tb_rst);
        wbSlaveModel.dat_o(wb_data_i);
        wbSlaveModel.dat_i(wb_data_o);
        wbSlaveModel.adr_i(wb_addr_o);
        wbSlaveModel.cyc_i(wb_cyc_o);
        wbSlaveModel.stb_i(wb_stb_o);
        wbSlaveModel.we_i(wb_we_o);
        wbSlaveModel.sel_i(wb_sel_o);
        wbSlaveModel.ack_o(wb_ack_i);
        wbSlaveModel.err_o(wb_err_i);
        wbSlaveModel.rty_o(wb_rty_i);

        // glitch_generator
        glitch_generator glitchGen1("glitchGen1");
        glitchGen1.glitch(i2c_clk);

        glitch_generator glitchGen2("glitchGen2");
        glitchGen2.glitch(i2c_data);
    }

    void clockCast()
    {
        sc_bit i2c_clk_bit;
        sc_bit i2c_data_bit;
        
        if((i2c_clk.read()!='z')&&(i2c_clk.read()!='x'))
        {
            i2c_clk_bit = i2c_clk.read();
            i2c_clk_b.write(i2c_clk_bit);
        }

        // if((i2c_data.read()!='z')&&(i2c_data.read()!='x')))
        // {
        //     i2c_data_bit = i2c_data.read();
        //     i2c_data_b.write(i2c_data_bit);
        // }
    }

    void tracing(sc_trace_file *tf)
    {
        cout << "INVOKED - "<< "tracing" << endl;
        const std::string str = this->name();
        
        // Dump local signals
        sc_trace(tf, this->tb_clk, str+".tb_clk");
        sc_trace(tf, this->tb_rst, str+".tb_rst");
    }

}; // end class tb_dut

#endif