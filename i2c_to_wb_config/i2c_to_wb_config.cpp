#include "systemc.h"
#include "i2c_to_wb_config.h"
#include <string>

void i2c_to_wb_config::process(void)
{
	bool		i2c_addr_ack_out_r;
	std::string	tmp_byte;


	tmp_byte = i2c_byte_in.read().to_string();
	//std::cout << "Value received: " << tmp_byte << "\n";

	if ((tmp_byte.compare("11110000") == 0) ||
	    (tmp_byte.compare("11110001") == 0)) {
		i2c_addr_ack_out_r = false;
	}
	else {
		i2c_addr_ack_out_r = true;
	}

	i2c_ack_out.write( tip_addr_ack ? i2c_addr_ack_out_r : false );
}

