#include "systemc.h"
#include "i2c_to_wb_top.h"

int sc_main (int argc, char* argv[]) 
{ 
  // -------------------------------------------> Define Ports
  sc_signal<bool>         i2c_data_in;
  //sc_clock i2c_data_in("i2c_data_in", 20, SC_NS, 0.5);
  sc_clock i2c_clk_in("i2c_clk_in", 20, SC_NS, 0.5);
  sc_signal<bool>         i2c_data_out;
  sc_signal<bool>         i2c_clk_out;
  sc_signal<bool>         i2c_data_oe;
  sc_signal<bool>         i2c_clk_oe;

  sc_signal< sc_bv<32> >  wb_data_i;
  sc_signal< sc_bv<32> >  wb_data_o;
  sc_signal< sc_bv<8> >   wb_addr_o;
  sc_signal< sc_bv<4> >   wb_sel_o;
  sc_signal<bool>         wb_we_o;
  sc_signal<bool>         wb_cyc_o;
  sc_signal<bool>         wb_stb_o;
  sc_signal<bool>         wb_ack_i;
  sc_signal<bool>         wb_err_i;
  sc_signal<bool>         wb_rty_i;

  sc_clock wb_clk_i("wb_clk_i", 2, SC_NS, 0.5);
  //sc_signal<bool>         wb_clk_i;
  sc_signal<bool>         wb_rst_i;

  // -------------------------------------------> DUT Instance
  i2c_to_wb_top i2c_to_wb_top_tb("i2c_to_wb_top");
    
    i2c_to_wb_top_tb.i2c_data_in(i2c_data_in);
    i2c_to_wb_top_tb.i2c_clk_in(i2c_clk_in);
    i2c_to_wb_top_tb.i2c_data_out(i2c_data_out);
    i2c_to_wb_top_tb.i2c_clk_out(i2c_clk_out);
    i2c_to_wb_top_tb.i2c_data_oe(i2c_data_oe);
    i2c_to_wb_top_tb.i2c_clk_oe(i2c_clk_oe);

    i2c_to_wb_top_tb.wb_data_i(wb_data_i);
    i2c_to_wb_top_tb.wb_data_o(wb_data_o);
    i2c_to_wb_top_tb.wb_addr_o(wb_addr_o);
    i2c_to_wb_top_tb.wb_sel_o(wb_sel_o);
    i2c_to_wb_top_tb.wb_we_o(wb_we_o);
    i2c_to_wb_top_tb.wb_cyc_o(wb_cyc_o);
    i2c_to_wb_top_tb.wb_stb_o(wb_stb_o);
    i2c_to_wb_top_tb.wb_ack_i(wb_ack_i);
    i2c_to_wb_top_tb.wb_err_i(wb_err_i);
    i2c_to_wb_top_tb.wb_rty_i(wb_rty_i);

    i2c_to_wb_top_tb.wb_clk_i(wb_clk_i);
    i2c_to_wb_top_tb.wb_rst_i(wb_rst_i);

  // -------------------------------------------> Setup .vcd
    // Open VCD file and configure time unit
    sc_trace_file *tf = sc_create_vcd_trace_file("i2c_to_wb_top");
    tf->set_time_unit(1, SC_NS);

    // Dump local signals
    sc_trace(tf, i2c_data_in,  "i2c_data_in");
    sc_trace(tf, i2c_clk_in,   "i2c_clk_in");
    sc_trace(tf, i2c_data_out, "i2c_data_out");
    sc_trace(tf, i2c_clk_out,  "i2c_clk_out");
    sc_trace(tf, i2c_data_oe,  "i2c_data_oe");
    sc_trace(tf, i2c_clk_oe,   "i2c_clk_oe");
    sc_trace(tf, wb_data_i,    "wb_data_i");
    sc_trace(tf, wb_data_o,    "wb_data_o");
    sc_trace(tf, wb_addr_o,    "wb_addr_o");
    sc_trace(tf, wb_sel_o,     "wb_sel_o");
    sc_trace(tf, wb_we_o,      "wb_we_o");
    sc_trace(tf, wb_cyc_o,     "wb_cyc_o");
    sc_trace(tf, wb_stb_o,     "wb_stb_o");
    sc_trace(tf, wb_ack_i,     "wb_ack_i");
    sc_trace(tf, wb_err_i,     "wb_err_i");
    sc_trace(tf, wb_rty_i,     "wb_rty_i");
    sc_trace(tf, wb_clk_i,     "wb_clk_i");
    sc_trace(tf, wb_rst_i,     "wb_rst_i");
    
    // Dump Internal module signals
    i2c_to_wb_top_tb.tracing(tf);

  cout << "@" << sc_time_stamp() <<" Initiating simulation\n" << endl;

  //sc_clock i2c_clk_in("i2c_clk_in", 2, SC_NS, 0.5);
  //sc_clock wb_clk_i("wb_clk_i", 2, SC_NS, 0.5);

  // Initial State;
  //i2c_data_in = 0;   
  //state =01                                 
  wb_data_i = "00000000000000000000000000000001";                            
  wb_ack_i = 0;                           
  wb_err_i = 0;                     
  wb_rty_i = 0;                                                
  wb_rst_i = 1;                      
  i2c_data_in = 1;  
  sc_start(100,SC_NS);
  
  // Inputs Change;
  //i2c_data_in = 1;  
  // state=02   
  wb_rst_i = 0;                       
  sc_start(28,SC_NS);
i2c_data_in = 0 ; 
sc_start(28,SC_NS);
i2c_data_in = 1 ; 
sc_start(28,SC_NS);
i2c_data_in = 0 ;                       
  sc_start(100,SC_NS);
  
//i2c_data_in = 1;  
  // state=03
 
  i2c_data_in = 1 ;                        
  sc_start(100,SC_NS);

  //sc_start(1000,SC_NS);
  
  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(tf);
  
  return 0;                                       // Terminate simulation
 }
