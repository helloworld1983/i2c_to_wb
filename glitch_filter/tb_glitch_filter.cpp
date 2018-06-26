#include "systemc.h"
#include "glitch_filter.h"

int sc_main (int argc, char* argv[]) 
{
    // -----------------------------------------> Module Definition
    // Inputs
    sc_clock clk("clk", 2, SC_NS, 0.5);
    sc_signal<bool>     in;
    // Outputs
    sc_signal<bool>    out;
    sc_signal<bool>    rise;
    sc_signal<bool>    fall;

    //sc_trace_file *tf = sc_create_vcd_trace_file("glitchFilter");

    // -----------------------------------------> DUT Instance
    // Instance Glitch Module
    glitchFilter glitchFilter_tb("glitchFilter");
      
      // Connect Inputs
      glitchFilter_tb.clk (clk);
      glitchFilter_tb.in  (in);
      // Connect Outputs
      glitchFilter_tb.out (out);
      glitchFilter_tb.rise(rise);
      glitchFilter_tb.fall(fall);

    // -----------------------------------------> Setup .vcd
    // Open VCD file
    sc_trace_file *tf = sc_create_vcd_trace_file("glitch_filter");
    
    // Dump local signals
    sc_trace(tf, clk,  "tb_clk");
    sc_trace(tf, in,   "tb_in");
    sc_trace(tf, out,  "tb_out");
    sc_trace(tf, rise, "tb_rise");
    sc_trace(tf, fall, "tb_fall");

    // Dump Internal module signals
    glitchFilter_tb.tracing(tf);
    
    // Configure timescale
    tf->set_time_unit(1, SC_NS);

    // -----------------------------------------> Start Simulation
    cout << "@" << sc_time_stamp() <<" >>>> TestBench Init\n" << endl;
  
    sc_start(10,SC_NS);
    in = false;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = true;
    sc_start(10,SC_NS);
    in = false;
    sc_start(10,SC_NS);
    in = false;
    sc_start(10,SC_NS);
    in = false;
    sc_start(10,SC_NS);

    
    cout << "@" << sc_time_stamp() <<" >>>> TestBench End\n" << endl;
    sc_close_vcd_trace_file(tf);
    return 0;// Terminate simulation

 }
