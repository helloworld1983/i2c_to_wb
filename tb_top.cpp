#include "systemc.h"
#include "tb_dut.h"

int sc_main (int, char *[]) 
{
    sc_clock tb_clk("tb_clk", 50, SC_NS, 0.5);
    sc_signal<bool> tb_rst;

    sc_trace_file *tf = sc_create_vcd_trace_file("tb_top");
    tf->set_time_unit(1, SC_PS);

    tb_dut dut("dut");
    dut.tb_clk(tb_clk);
    dut.tb_rst(tb_rst);
    dut.tracing(tf);
    
    // the_test test("test");
    // test.tb_clk(tb_clk);
    // test.tb_rst(tb_rst);

    sc_start(0,SC_NS);

    cout << "@" << sc_time_stamp()<< endl;
    
    sc_start(100,SC_NS); 

    dut.i2cMasterModel.start();
    // dut.i2cMasterModel.write_byte(241); //f1
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(1);
    
    // dut.i2cMasterModel.start();
    // dut.i2cMasterModel.write_byte(16); //10
    // dut.i2cMasterModel.write_byte(171); //ab
    // dut.i2cMasterModel.write_byte(186); //ba
    
    // dut.i2cMasterModel.start();
    // dut.i2cMasterModel.write_byte(240); //f0
    // dut.i2cMasterModel.write_byte(190); //be
    // dut.i2cMasterModel.write_byte(239); //ef
    
    // dut.i2cMasterModel.start();
    // dut.i2cMasterModel.write_byte(203); //cb
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(1);
    
    // dut.i2cMasterModel.start();
    // dut.i2cMasterModel.write_byte(241); //f1
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(1);
    
    // dut.i2cMasterModel.start();
    // dut.i2cMasterModel.write_byte(219); //db
    // dut.i2cMasterModel.read_byte(0);
    // dut.i2cMasterModel.read_byte(1);
    //dut.i2cMasterModel.stop();
    sc_start(1000,SC_NS); 

    cout << "@" << sc_time_stamp()<< endl;

    return 0;
}