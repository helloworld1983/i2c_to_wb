#include "systemc.h"
#include "i2c_to_wb_if.h"

typedef sc_bv<32> DW; 
typedef sc_bv<8> AW;

int sc_main (int, char *[]) {

    sc_signal<bool>        i2c_data;
    sc_signal<bool>        i2c_ack_done;
    sc_signal< AW >          i2c_byte_in;
    sc_signal< AW >         i2c_byte_out;
    sc_signal<bool>       i2c_parallel_load;
    sc_signal<bool>        tip_wr_ack;
    sc_signal<bool>        tip_rd_ack;
    sc_signal<bool>       tip_addr_ack;

    sc_signal<DW>          wb_data_i;
    sc_signal<DW>         wb_data_o;
    sc_signal<AW>         wb_addr_o;
    sc_signal< sc_bv<2> >  wb_sel_o;
    sc_signal<bool>       wb_we_o;
    sc_signal<bool>       wb_cyc_o;
    sc_signal<bool>       wb_stb_o;
    sc_signal<bool>        wb_ack_i;
    sc_signal<bool>        wb_err_i;
    sc_signal<bool>        wb_rty_i;
    sc_signal<bool>        wb_rst_i;
    sc_signal<sc_int<8> >  state;
    sc_signal<sc_int<8> >  next_state;

    sc_clock          wb_clk_i("wb_clk_i", 2, SC_NS ,0.5);
  
  //sc_clock clock("clock", 10, 0.5, 1, false);
  //sc_clock clock("clock", 2, SC_NS ,0.5);

    i2c_to_wb_if i2cwb ("i2cwb");
    i2cwb.wb_clk_i(wb_clk_i);
    i2cwb.i2c_data(i2c_data);
    i2cwb.i2c_ack_done(i2c_ack_done);
    i2cwb.i2c_byte_in(i2c_byte_in);
    i2cwb.i2c_byte_out(i2c_byte_out);
    i2cwb.i2c_parallel_load(i2c_parallel_load);
    i2cwb.tip_wr_ack(tip_wr_ack);
    i2cwb.tip_rd_ack(tip_rd_ack);
    i2cwb.tip_addr_ack(tip_addr_ack);
    i2cwb.wb_data_i(wb_data_i);
    i2cwb.wb_data_o(wb_data_o);
    i2cwb.wb_addr_o(wb_addr_o);
    i2cwb.wb_sel_o(wb_sel_o);
    i2cwb.wb_we_o(wb_we_o);
    i2cwb.wb_cyc_o(wb_cyc_o);
    i2cwb.wb_stb_o(wb_stb_o);
    i2cwb.wb_ack_i(wb_ack_i);
    i2cwb.wb_err_i(wb_err_i);
    i2cwb.wb_rty_i(wb_rty_i);
    i2cwb.wb_rst_i(wb_rst_i);
    i2cwb.next_state(next_state);
    i2cwb.state(state);
    


     // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("i2c_to_wb_if");
    wf->set_time_unit(1, SC_NS);

    // Dump the desired signals
    sc_trace(wf, wb_clk_i, "wb_clk_i");
    sc_trace(wf, i2c_data, "i2c_data");
    sc_trace(wf, i2c_ack_done, "i2c_ack_done");
    sc_trace(wf, i2c_byte_in, "i2c_byte_in");
    sc_trace(wf, i2c_byte_out, "i2c_byte_out");
    sc_trace(wf, i2c_parallel_load, "i2c_parallel_load");
    sc_trace(wf, tip_wr_ack, "tip_wr_ack");
    sc_trace(wf, tip_addr_ack, "tip_addr_ack");
    sc_trace(wf, wb_data_i, "wb_data_i");
    sc_trace(wf, wb_data_o, "wb_data_o");
    sc_trace(wf, wb_addr_o, "wb_addr_o");
    sc_trace(wf, wb_sel_o, "wb_sel_o");
    sc_trace(wf, wb_we_o, "wb_we_o");
    sc_trace(wf, wb_cyc_o, "wb_cyc_o");
    sc_trace(wf, wb_stb_o, "wb_stb_o");
    sc_trace(wf, wb_ack_i, "wb_ack_i");
    sc_trace(wf, wb_err_i, "wb_err_i");
    sc_trace(wf, wb_rty_i, "wb_rty_i");
    sc_trace(wf, wb_rst_i, "wb_rst_i");
    sc_trace(wf, state, "state");
    sc_trace(wf, next_state, "next_state");

    // 0 ns
    sc_start(0,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    // Initialize all variables
    i2c_data = 0;       // initial value of reset

    
    // 10 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
     i2c_data = 0;
    i2c_ack_done = 0;
    tip_addr_ack = 0;
    i2c_byte_in = "00000000";
    tip_wr_ack = 0;
    tip_rd_ack = 0;
    wb_data_i = 0;
    wb_rst_i = 1;

    // 20ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 1;
    i2c_ack_done = 0;
    tip_addr_ack = 0;
    i2c_byte_in = "00000000";
    tip_wr_ack = 0;
    tip_rd_ack = 0;
    wb_data_i = 0;
    wb_rst_i = 0; 
    
    //30 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 1;
    i2c_ack_done = 1;
    tip_addr_ack = 1;
    i2c_byte_in = "0110001";
    tip_wr_ack = 0;
    tip_rd_ack = 0;
    wb_data_i = 0;
    wb_rst_i = 0; 

    // 40 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 1;
    i2c_ack_done = 1;
    tip_addr_ack = 1;
    i2c_byte_in = "11111101";
    tip_wr_ack = 1;
    tip_rd_ack = 1;
    wb_data_i = 1;
    wb_rst_i = 0;

    // 50 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 1;
    i2c_ack_done = 1;
    tip_addr_ack = 1;
    i2c_byte_in = "01000111";
    tip_wr_ack = 1;
    tip_rd_ack = 1;
    wb_data_i = 1;
    wb_rst_i = 0;

    // 50 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 0;
    i2c_ack_done = 1;
    tip_addr_ack = 1;
    i2c_byte_in = "10000011";
    tip_wr_ack = 1;
    tip_rd_ack = 1;
    wb_data_i = 1;
    wb_rst_i = 0;

    // 60 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 1;
    i2c_ack_done = 1;
    tip_addr_ack = 1;
    i2c_byte_in = "00001011";
    tip_wr_ack = 1;
    tip_rd_ack = 1;
    wb_data_i = 0;
    wb_rst_i = 0;

    //70 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 0;
    i2c_ack_done = 1;
    tip_addr_ack = 1;
    i2c_byte_in = "00111111";
    tip_wr_ack = 0;
    tip_rd_ack = 0;
    wb_data_i = 0;
    wb_rst_i = 0;

    // 80 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 1;
    i2c_ack_done = 0;
    tip_addr_ack = 1;
    i2c_byte_in = "11000011";
    tip_wr_ack = 0;
    tip_rd_ack = 0;
    wb_data_i = 0;
    wb_rst_i = 1;

    //90 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 1;
    i2c_ack_done = 0;
    tip_addr_ack = 1;
    i2c_byte_in = "11001011";
    tip_wr_ack = 1;
    tip_rd_ack = 0;
    wb_data_i = 1;
    wb_rst_i = 0;
    
    //100 ns
    sc_start(10,SC_NS);
    cout << "@" << sc_time_stamp()<< endl;
    i2c_data = 0;
    i2c_ack_done = 1;
    tip_addr_ack = 1;
    i2c_byte_in = "00000101";
    tip_wr_ack = 0;
    tip_rd_ack = 0;
    wb_data_i = 1;
    wb_rst_i = 0;

    cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0;// Terminate simulation
}