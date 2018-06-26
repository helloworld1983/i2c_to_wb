#include "systemc.h"
#include "i2c_to_wb_config.h"
#include <string>

void i2c_to_wb_config::process(void)
{
	bool i2c_addr_ack_out_r;
	std::string	tmp_byte;

	if ((i2c_byte_in.read() == 0xF0) || 
	    (i2c_byte_in.read() == 0xF1))
	{
		i2c_addr_ack_out_r = false;
	}
	else 
	{
		i2c_addr_ack_out_r = true;
	}

	i2c_ack_out.write( tip_addr_ack ? i2c_addr_ack_out_r : false );
}

void i2c_to_wb_config::tracing(sc_trace_file *tf)
{
	cout << "[VCD]" << "Add I2C to WB Config Signals to .VCD\n" << endl;
	const std::string str = this->name();

	// Dump local signals
	sc_trace(tf, this->i2c_byte_in, str+".i2c_byte_in");
	sc_trace(tf, this->tip_addr_ack, str+".tip_addr_ack");
	sc_trace(tf, this->i2c_ack_out, str+".i2c_ack_out");
	sc_trace(tf, this->wb_clk_i, str+".wb_clk_i");
	sc_trace(tf, this->wb_rst_i, str+".wb_rst_i");
}
