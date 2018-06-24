#include "systemc.h"
#include "./i2c_to_wb_fsm/i2c_to_wb_fsm.h"
#include "./glitch_filter/glitch_filter.cpp"
#include "./i2c_to_wb_config/i2c_to_wb_config.h"
#include "./i2c_to_wb_if/i2c_to_wb_if.h"

// Define Module
SC_MODULE (i2c_to_wb_top) 
{
    // -----------------------------------------> Define Ports
    sc_in<bool>             i2c_data_in;
    sc_in<bool>             i2c_clk_in;
    sc_out<bool>            i2c_data_out;
    sc_out<bool>            i2c_clk_out;
    sc_out<bool>            i2c_data_oe;
    sc_out<bool>            i2c_clk_oe;

    sc_in< sc_uint<32> >    wb_data_i;
    sc_out< sc_uint<32> >   wb_data_o;
    sc_out< sc_uint<8> >    wb_addr_o;
    sc_out< sc_uint<4> >    wb_sel_o;
    sc_out<bool>            wb_we_o;
    sc_out<bool>            wb_cyc_o;
    sc_out<bool>            wb_stb_o;
    sc_in<bool>             wb_ack_i;
    sc_in<bool>             wb_err_i;
    sc_in<bool>             wb_rty_i;

    sc_in<bool>             wb_clk_i;
    sc_in<bool>             wb_rst_i;

    // -----------------------------------------> Variables
    
    // Verilog
    // reg  [8:0]  i2c_data_in_r;
    // wire        serial_out = i2c_data_in_r[8];
    
    // SystemC
    sc_uint<9> i2c_data_in_r;
    sc_signal<bool> serial_out = i2c_data_in_r[8];
    

    ////////////////// FALTA LOGICA

    // -----------------------------------------> Wires

    sc_signal<bool>         tip_addr_byte;
    sc_signal<bool>         tip_read_byte;
    sc_signal<bool>         tip_write_byte;
    sc_signal<bool>         tip_wr_ack;
    sc_signal<bool>         tip_rd_ack;
    sc_signal<bool>         tip_addr_ack;

    sc_signal<bool>         i2c_ack_out;
    sc_signal<bool>         i2c_ack_done;

    sc_signal< sc_bv<8> >   i2c_byte_out;
    sc_signal<bool>         i2c_parallel_load;

    // Glitch Filter (data)
    sc_signal<bool>         gf_i2c_data_in;
    sc_signal<bool>         gf_i2c_data_in_rise;
    sc_signal<bool>         gf_i2c_data_in_fall;

    // Glitch Filter (clock)
    sc_signal<bool>         gf_i2c_clk_in;
    sc_signal<bool>         gf_i2c_clk_in_rise;
    sc_signal<bool>         gf_i2c_clk_in_fall;

    // -----------------------------------------> Module Instances
    // Instance Glitch Modules
    glitchFilter i_gf_i2c_data_in;
    glitchFilter i_gf_i2c_clk_in;
    // Instance Finite State Machine
    i2c_to_wb_fsm i_i2c_to_wb_fsm;
    // Instance Config
    i2c_to_wb_config i_i2c_to_wb_config;
    // "If"
    i2c_to_wb_if i_i2c_to_wb_if;

    // -----------------------------------------> Define Methods
    void templateCppMethod();
    void templateSystemcMethod();

    // Constructor
    SC_CTOR(i2c_to_wb_top) : i_gf_i2c_data_in("topDataGlitchFilter"),
                             i_gf_i2c_clk_in("topClockGlitchFilter"),
                             i_i2c_to_wb_fsm("topFSM"),
                             i_i2c_to_wb_config("topConfig"),
                             i_i2c_to_wb_if("i_i2c_to_wb_if")

    {
        // -------------------------------------> Glitch Filter 
        // Connect Inputs
        i_gf_i2c_data_in.clk (wb_clk_i);
        i_gf_i2c_data_in.in  (i2c_data_in);
        // Connect Outputs
        i_gf_i2c_data_in.out (gf_i2c_data_in);
        i_gf_i2c_data_in.rise(gf_i2c_data_in_rise);
        i_gf_i2c_data_in.fall(gf_i2c_data_in_fall);

        // -------------------------------------> Glitch Filter
        // Connect Inputs
        i_gf_i2c_clk_in.clk (wb_clk_i);
        i_gf_i2c_clk_in.in  (i2c_clk_in);
        // Connect Outputs
        i_gf_i2c_clk_in.out (gf_i2c_clk_in);
        i_gf_i2c_clk_in.rise(gf_i2c_clk_in_rise);
        i_gf_i2c_clk_in.fall(gf_i2c_clk_in_fall);

        // -------------------------------------> FSM
        
        i_i2c_to_wb_fsm.i2c_data_rise(gf_i2c_data_in_rise);
        i_i2c_to_wb_fsm.i2c_data_fall(gf_i2c_data_in_fall);
        i_i2c_to_wb_fsm.i2c_clk(gf_i2c_clk_in);
        // i2c.start_detected(start_detected);
        // i2c.stop_detected(stop_detected);
        i_i2c_to_wb_fsm.wb_rst_i(wb_rst_i);
        i_i2c_to_wb_fsm.wb_clk_i(wb_clk_i);
        //i2c.nxt_st(nxt_st);
        //i_i2c_to_wb_fsm.state_out();                              // problema N/C
        i_i2c_to_wb_fsm.i2c_clk_rise(gf_i2c_clk_in_rise);
        i_i2c_to_wb_fsm.i2c_clk_fall(gf_i2c_clk_in_fall);
        //i2c.xmt_byte_done(xmt_byte_done);
        //i2c.bit_count(bit_count);
        //i2c.tip_ack(tip_ack);
        i_i2c_to_wb_fsm.i2c_ack_done(i2c_ack_done);
        i_i2c_to_wb_fsm.i2c_ack_out(i2c_ack_out);
        i_i2c_to_wb_fsm.i2c_data(gf_i2c_data_in);
        i_i2c_to_wb_fsm.i2c_r_w_bit(i2c_data_in_r[0]);              // problema sc_bool
        i_i2c_to_wb_fsm.tip_addr_byte(tip_addr_byte);
        i_i2c_to_wb_fsm.tip_addr_ack(tip_addr_ack);
        i_i2c_to_wb_fsm.tip_read_byte(tip_read_byte);
        i_i2c_to_wb_fsm.tip_write_byte(tip_write_byte);  
        i_i2c_to_wb_fsm.tip_wr_ack(tip_wr_ack);      
        i_i2c_to_wb_fsm.tip_rd_ack(tip_rd_ack);
        //i_i2c_to_wb_fsm.i2c_error();                              // problema N/C
        

        // -------------------------------------> Config
        /*
        i_i2c_to_wb_config.i2c_byte_in(i2c_data_in_r);              // problema sc_lv
        i_i2c_to_wb_config.tip_addr_ack(tip_addr_ack);
        i_i2c_to_wb_config.i2c_ack_out(i2c_ack_out);
        i_i2c_to_wb_config.wb_clk_i(wb_clk_i);
        i_i2c_to_wb_config.wb_rst_i(wb_rst_i);
        */

        // -------------------------------------> "if"
        /*
        i_i2c_to_wb_if.i2c_data(gf_i2c_data_in);
        i_i2c_to_wb_if.i2c_ack_done(i2c_ack_done);
        i_i2c_to_wb_if.i2c_byte_in(i2c_data_in_r);                  // problema sc_bv
        i_i2c_to_wb_if.i2c_byte_out(i2c_byte_out);                  // problema sc_bv
        i_i2c_to_wb_if.i2c_parallel_load(i2c_parallel_load);
        i_i2c_to_wb_if.tip_wr_ack(tip_wr_ack);
        i_i2c_to_wb_if.tip_rd_ack(tip_rd_ack);
        i_i2c_to_wb_if.tip_addr_ack(tip_addr_ack);

        i_i2c_to_wb_if.wb_data_i(wb_data_i);                        // problema sc_bv
        i_i2c_to_wb_if.wb_data_o(wb_data_o);                        // problema sc_bv
        i_i2c_to_wb_if.wb_addr_o(wb_addr_o);                        // problema sc_bv
        i_i2c_to_wb_if.wb_sel_o(wb_sel_o);
        i_i2c_to_wb_if.wb_we_o(wb_we_o);
        i_i2c_to_wb_if.wb_cyc_o(wb_cyc_o);
        i_i2c_to_wb_if.wb_stb_o(wb_stb_o);
        i_i2c_to_wb_if.wb_ack_i(wb_ack_i);
        i_i2c_to_wb_if.wb_err_i(wb_err_i);
        i_i2c_to_wb_if.wb_rty_i(wb_rty_i);

        i_i2c_to_wb_if.wb_clk_i(wb_clk_i);
        i_i2c_to_wb_if.wb_rst_i(wb_rst_i);
        */

        // -------------------------------------> Methods
        SC_METHOD(templateSystemcMethod);
    }
    
};  // End of Module
