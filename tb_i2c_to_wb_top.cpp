#include "systemc.h"
#include "i2c_to_wb_top.h"

int sc_main (int argc, char* argv[]) {
  sc_signal<bool>   i2c_clk_io;
  sc_signal<bool>   i2c_data_io;
  
  //glitchFilter i_gf_i2c_data_in("glitchFilter");

  // Open VCD file
  sc_trace_file *tf = sc_create_vcd_trace_file("i2c_to_wb_top");
  tf->set_time_unit(1, SC_NS);
  
  // Dump the desired signals
  sc_trace(tf, i2c_clk_io, "i2c_clk_io");
  
  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  
  sc_start(10,SC_NS);
  
  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(tf);
  return 0;// Terminate simulation

 }
