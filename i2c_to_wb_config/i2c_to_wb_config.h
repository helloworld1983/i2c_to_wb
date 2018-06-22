#include "systemc.h"

SC_MODULE(i2c_to_wb_config)
{
	sc_in<sc_lv<8> >	i2c_byte_in;
	sc_in<bool>		tip_addr_ack;
	sc_out<bool>		i2c_ack_out;


	sc_in_clk		wb_clk_i;
	sc_in<bool>		wb_rst_i;

	void process( void );

	SC_CTOR(i2c_to_wb_config)
	{

		 SC_METHOD(process);
		 sensitive << i2c_byte_in;
		 sensitive << tip_addr_ack;
		 sensitive << wb_clk_i.pos();
		 sensitive << wb_rst_i;
	}
};

