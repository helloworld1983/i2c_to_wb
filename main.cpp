#include "systemc.h"
#include "glitch_generator.h"

int sc_main (int, char *[]) {
    
    sc_signal<sc_logic> glitch_in;
    sc_signal<sc_logic> glitch_out;

    sc_logic wValue;
    // Connect the DUT
    glitch_generator glitchGen("glitchGen");
    glitchGen.in(glitch_in);
    glitchGen.out(glitch_out);

 
    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("glitch_generator");
    wf->set_time_unit(1, SC_NS);
    // Dump the desired signals
    sc_trace(wf, glitch_in, "in");
    sc_trace(wf, glitch_out, "out");
    
    sc_start(0,SC_NS);

    cout << "@" << sc_time_stamp()<< endl;
    for (int i=0;i<100000;i++) 
    {
        wValue = '0';
        glitch_in.write(wValue);
        sc_start(1000,SC_NS);
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