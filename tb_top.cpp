#include "systemc.h"
#include "tb_dut.h"

int sc_main (int, char *[]) 
{
    sc_clock tb_clk("tb_clk", 50, SC_NS, 0.5);
    sc_signal<bool> tb_rst;

    tb_dut dut("dut");
    dut.tb_clk(tb_clk);
    dut.tb_rst(tb_rst);
    
    // the_test test("test");
    // test.tb_clk(tb_clk);
    // test.tb_rst(tb_rst);

    sc_start(0,SC_NS);

    cout << "@" << sc_time_stamp()<< endl;
    
    sc_start(1000,SC_NS); 

    cout << "@" << sc_time_stamp()<< endl;

    return 0;
}