#include "i2c_to_wb_top.h"

/*
- Function          i2cDataShiftRegister
- Sensitivity List  wb_clk_i.pos()

- Description       Algo hara ...
*/
void i2c_to_wb_top::i2cDataShiftRegister()
{
    cout << "INVOKED - " << "i2cDataShiftRegister" << endl;

    if (i2c_parallel_load)
    {
        i2c_data_in_r = i2c_byte_out;

    }
    else if ( (tip_write_byte & gf_i2c_clk_in_rise) | (tip_read_byte & gf_i2c_clk_in_fall) )
    {
        i2c_data_in_r = (i2c_data_in_r.range(7,0), gf_i2c_data_in);
    }
}

/*
- Function          i2cDataOutOfSync
- Sensitivity List  wb_clk_i.pos()

- Description       Algo hara ...
*/
void i2c_to_wb_top::i2cDataOutOfSync()
{
    cout << "INVOKED - " << "i2cDataOutOfSync" << endl;

    if (wb_rst_i.read())
    {
        i2c_data_oe_r = 0;
    }
    else if (gf_i2c_clk_in_fall.read())
    {
        i2c_data_oe_r = (tip_read_byte.read() | tip_wr_ack.read());
        i2c_data_mux_select_r = (tip_wr_ack.read());
    }

}

/*
- Function          assigns
- Sensitivity List  *

- Description       Algo hara ...
*/
void i2c_to_wb_top::assigns()
{
    cout << "INVOKED - " << "assigns" << endl;

    i2c_data_out.write(i2c_data_mux_select_r ? i2c_ack_out.read() : serial_out.read());
    i2c_data_oe.write(i2c_data_oe_r);
    i2c_clk_out.write(1);
    i2c_clk_oe.write(0);

    // Transformation variables
    t_i2c_r_w_bit = static_cast<bool>(i2c_data_in_r[0]);
    t_serial_out = static_cast<bool>(i2c_data_in_r[8]);
    t_i2c_8bit_data_in_r = i2c_data_in_r.range(7,0);
    t_i2c_8bv_data_in_r = static_cast<sc_bv<8> >(t_i2c_8bit_data_in_r);

    i2c_r_w_bit.write(t_i2c_r_w_bit);
    serial_out.write(t_serial_out);
    i2c_8uint_data_in_r.write(t_i2c_8bit_data_in_r);
    i2c_8bv_data_in_r.write(t_i2c_8bit_data_in_r);
}

/*
- Function          tracing
- Sensitivity List  *

- Description       Algo hara ...
*/
void i2c_to_wb_top::tracing(sc_trace_file *tf)
{
    cout << "INVOKED - " << "tracing i2c TOP" << endl;
    const std::string str = this->name();

    // Dump local signals
    sc_trace(tf, this->i2c_data_in, str+".i2c_data_in");
    sc_trace(tf, this->i2c_clk_in, str+".i2c_clk_in");
    sc_trace(tf, this->i2c_data_out, str+".i2c_data_out");
    sc_trace(tf, this->i2c_clk_out, str+".i2c_clk_out");
    sc_trace(tf, this->i2c_data_oe, str+".i2c_data_oe");
    sc_trace(tf, this->i2c_clk_oe, str+".i2c_clk_oe");

    sc_trace(tf, this->wb_data_i, str+".wb_data_i");
    sc_trace(tf, this->wb_data_o, str+".wb_data_o");
    sc_trace(tf, this->wb_addr_o, str+".wb_addr_o");
    sc_trace(tf, this->wb_sel_o, str+".wb_sel_o");

    sc_trace(tf, this->wb_we_o, str+".wb_we_o");
    sc_trace(tf, this->wb_cyc_o, str+".wb_cyc_o");
    sc_trace(tf, this->wb_stb_o, str+".wb_stb_o");
    sc_trace(tf, this->wb_ack_i, str+".wb_ack_i");
    sc_trace(tf, this->wb_err_i, str+".wb_err_i");
    sc_trace(tf, this->wb_rty_i, str+".wb_rty_i");

    sc_trace(tf, this->wb_clk_i, str+".wb_clk_i");
    sc_trace(tf, this->wb_rst_i, str+".wb_rst_i");

    // Dump Internal Modules Signals
    i_gf_i2c_data_in.tracing(tf);
    i_gf_i2c_clk_in.tracing(tf);
    i_i2c_to_wb_fsm.tracing(tf);
    //i_i2c_to_wb_config.tracing(tf);
    i_i2c_to_wb_if.tracing(tf);
}
