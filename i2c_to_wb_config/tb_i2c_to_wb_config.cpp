#include <systemc.h>
#include "i2c_to_wb_config.h"

void test_value(sc_signal<sc_uint<8>> *byte);

int sc_main(int argc, char* argv[])
{
	// Local Variables
	sc_signal< sc_uint<8> >	i2c_byte_in;
	sc_signal<bool>		tip_addr_ack;
	sc_signal<bool>		i2c_ack_out;

	sc_signal<bool>		wb_rst_i;
	sc_clock 		wb_clk_i("clock", 2, SC_NS, 0.5); 

	// Create VCD file
	sc_trace_file *wf = sc_create_vcd_trace_file("i2c_to_wb_config");
	wf->set_time_unit(1, SC_NS);

	// Create Configuration class
	i2c_to_wb_config config("Config");
	config.i2c_byte_in(i2c_byte_in);
	config.tip_addr_ack(tip_addr_ack);
	config.i2c_ack_out(i2c_ack_out);
	config.wb_clk_i(wb_clk_i);
	config.wb_rst_i(wb_rst_i);

	// Set default values
	i2c_byte_in = 0;
	tip_addr_ack = false;
	wb_rst_i = false;

	sc_trace(wf, i2c_byte_in, "i2c_byte_in");
	sc_trace(wf, tip_addr_ack, "tip_addr_ack");
	sc_trace(wf, i2c_ack_out, "i2c_ack_out");
	sc_trace(wf, wb_clk_i, "wb_clk_i");
	sc_trace(wf, wb_rst_i, "wb_rst_i");

	// tip addr ack is false, so output should be low always
	tip_addr_ack = false;
	wb_rst_i = false;
	test_value(&i2c_byte_in);

	// tip addr ack is true, so output should be high when 0xF0 and 0xF1 is
	// received
	tip_addr_ack = true;
	wb_rst_i = false;
	test_value(&i2c_byte_in);
	
	// tip addr is false, wb reset is true, output should be low always
	tip_addr_ack = false;
	wb_rst_i = true;
	test_value(&i2c_byte_in);

	sc_start(100, SC_NS);
	sc_close_vcd_trace_file(wf);

	return 0;
}

void test_value(sc_signal<sc_uint<8>> *byte)
{
	(*byte) = 0x00;
	sc_start(10, SC_NS);

	(*byte) = 0x01;
	sc_start(10, SC_NS);

	//(*byte) = "0000000X";
	//sc_start(10, SC_NS);

	//(*byte) = "0000000Z";
	//sc_start(10, SC_NS);

	(*byte) = 0xF0;
	sc_start(10, SC_NS);

	(*byte) = 0xF1;
	sc_start(10, SC_NS);

	//(*byte) = "1111000X";
	//sc_start(10, SC_NS);

	//(*byte) = "1111000Z";
	//sc_start(10, SC_NS);

	(*byte) = 0xFF;
	sc_start(10, SC_NS);

	//(*byte) = "XXXXXXXX";
	//sc_start(10, SC_NS);

	//(*byte) = "ZZZZZZZZ";
	//sc_start(10, SC_NS);

	//(*byte) = "XXXX0000";
	//sc_start(10, SC_NS);

	//(*byte) = "0000XXXX";
	//sc_start(10, SC_NS);

	//(*byte) = "XXXX1111";
	//sc_start(10, SC_NS);

	//(*byte) = "1111XXXX";
	//sc_start(10, SC_NS);

	//(*byte) = "XXXXZZZZ";
	//sc_start(10, SC_NS);

	//(*byte) = "ZZZZXXXX";
	//sc_start(10, SC_NS);
}
