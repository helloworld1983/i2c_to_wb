#include "systemc.h"
#include "wb_slave_model.h"

int sc_main (int, char *[]) 
{      
    //sc_signal<bool>                 clk_i;
    sc_clock clk_i("clk_i", 50, SC_NS, 0.5);
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

    sc_logic wValue;

    // Connect the DUT
    wb_slave_model wbSlaveModel("wbSlaveModel");
    wbSlaveModel.clk_i(clk_i);
    wbSlaveModel.rst_i(rst_i);
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

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("wb_slave_model");
    wf->set_time_unit(1, SC_NS);
    // Dump the desired signals
    sc_trace(wf, clk_i, "clk_i");
    sc_trace(wf, rst_i, "rst_i");
    sc_trace(wf, dat_o, "dat_o");
    sc_trace(wf, dat_i, "dat_i");
    sc_trace(wf, adr_i, "adr_i");
    sc_trace(wf, cyc_i, "cyc_i");
    sc_trace(wf, stb_i, "stb_i");
    sc_trace(wf, we_i, "we_i");
    sc_trace(wf, sel_i, "sel_i");
    sc_trace(wf, ack_o, "ack_o");
    sc_trace(wf, err_o, "err_o");
    sc_trace(wf, rty_o, "rty_o");

    dat_i.write(1234);
    adr_i.write(26);

    sc_start(0,SC_NS);

    cout << "@" << sc_time_stamp()<< endl;
    
    sc_start(100,SC_NS);  

    sel_i.write(1);      
    sc_start(100,SC_NS);    
    cyc_i.write(1); 
    sc_start(100,SC_NS);   
    we_i.write(1); 
    sc_start(100,SC_NS);  
    stb_i.write(1); 
    sc_start(100,SC_NS);  
    sel_i.write(2);  
    sc_start(500,SC_NS);       
    we_i.write(0); 
    sc_start(100,SC_NS);  
    stb_i.write(0); 
    sc_start(600,SC_NS);
    cyc_i.write(0); 
    sc_start(500,SC_NS); 


    cout << "@" << sc_time_stamp()<< endl;
    
    sc_close_vcd_trace_file(wf);

   return 0;
}