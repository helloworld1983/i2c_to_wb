#include "systemc.h"
#include "glitch_generator.h"
#include "wb_slave_model.h"

int sc_main (int, char *[]) 
{
    
    sc_signal<sc_logic> glitch_in;
    sc_signal<sc_logic> glitch_out;

    sc_signal<bool>                 clk_i;
    sc_signal<bool>                 rst_i;
    sc_signal<sc_uint<(DWIDTH)> >  dat_o;
    sc_signal<sc_uint<(DWIDTH)> >   dat_i;
    sc_signal<sc_uint<(AWIDTH)> >   adr_i;
    sc_signal<bool>                 cyc_i;
    sc_signal<bool>                 stb_i;
    sc_signal<bool>                 we_i;
    sc_signal<sc_uint<(DWIDTH)/8> > sel_i;
    sc_signal<bool>                ack_o;
    sc_signal<bool>                err_o;
    sc_signal<bool>                rty_o;

    sc_logic wValue;

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

    // Connect the DUT
    glitch_generator glitchGen("glitchGen");
    glitchGen.in(glitch_in);
    glitchGen.out(glitch_out);

 
    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("model");
    wf->set_time_unit(1, SC_NS);
    // Dump the desired signals
    sc_trace(wf, glitch_in, "in");
    sc_trace(wf, glitch_out, "out");
    // wbSlave
    sc_trace(wf, glitch_in, "in");
    sc_trace(wf, glitch_out, "out");
    
    sc_start(0,SC_NS);

    cout << "@" << sc_time_stamp()<< endl;
    for (int i=0;i<100;i++) 
    {
        wValue = '0';
        glitch_in.write(wValue);
        sc_start(500,SC_NS);
        cout << "@" << sc_time_stamp()<<" Signal:" <<glitch_in.read() <<endl;
        wValue = '1';
        glitch_in.write(wValue);
        sc_start(100,SC_NS);
        cout << "@" << sc_time_stamp()<<" Signal:" <<glitch_in.read() <<endl;
    }
    cout << "@" << sc_time_stamp()<< endl;
    
    sc_close_vcd_trace_file(wf);

   return 0;
}