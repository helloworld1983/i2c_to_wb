#include <systemc.h>
#include "i2c_to_wb_if.h" 

//  state machine

  const sc_int<8>  STATE_IDLE       = 1;
  const sc_int<8>  STATE_WRITE      = 2;
  const sc_int<8>  STATE_WRITE_WAIT = 3;
  const sc_int<8>  STATE_READ       = 4;
  const sc_int<8>  STATE_READ_WAIT  = 5; 



/*
* @fn  tracing()
* 
* @details     Common method for all modules, passes the pointer
*              to .vcd dump file
*/
void i2c_to_wb_if::tracing(sc_trace_file *tf)
{
    cout << "[VCD]" << "Add glitchFilter Signals to .VCD\n" << endl;
    const std::string str = this->name();

    // Dump local signals
    sc_trace(tf, this->i2c_r_w_bit, str+".i2c_r_w_bit");
    sc_trace(tf, this->i2c_offset_r, str+".i2c_offset_r");
}

/*
* @fn  getfirstbit()
* 
* @details     Sets the first bit of i2c_byte_in to local var i2c_r_w_bit.
*/
void i2c_to_wb_if::getfirstbit()
{
    sc_bv<1> temp = static_cast< sc_bv<1> >(i2c_byte_in.read().get_bit(0));
    i2c_r_w_bit = (temp);
}

/*
* @fn  fsm_main()
* 
* @details     Main finite state machine.
*/
void i2c_to_wb_if::fsm_main()
{ 
    cout << "wb_rst_i: " << wb_rst_i << "\n" ; 
    if(wb_rst_i)
    {
        state.write(STATE_IDLE);
    }
    else
    {
        cout << "next state: " << next_state << "\n"; 
        state.write(next_state.read());
    }
}

/*
* @fn  fsm_aux()
* 
* @details     Secondary finite state machine.
*/
void i2c_to_wb_if::fsm_aux()
{
   
    if(state == STATE_IDLE)
    {
        if( tip_addr_ack & i2c_ack_done )
        {
            if(i2c_r_w_bit[0] == "1")
                next_state = (STATE_READ);
            else
                next_state = (STATE_WRITE_WAIT);
        }
        else
        {
            next_state = (STATE_IDLE);
        }            
    }
    else if(state == STATE_WRITE)
    {
        if( wb_ack_i )
        {
            next_state = (STATE_WRITE_WAIT);
        }
        else
        {
            next_state =(STATE_WRITE);
        }
    }
    else if(state == STATE_WRITE_WAIT)
    {
        if( tip_addr_ack )
        {
            next_state = (STATE_IDLE);
        }
        else
        {
            if( tip_wr_ack & i2c_ack_done )
                next_state = (STATE_WRITE);
            else  
                next_state = (STATE_WRITE_WAIT);
        }
    }
    else if(state == STATE_READ)
    {
        if( wb_ack_i )
            next_state = (STATE_READ_WAIT);
        else
            next_state = (STATE_READ);
    }
    else if(state == STATE_READ_WAIT)
    {
        if( tip_addr_ack )
        {
            next_state = (STATE_IDLE);
        }
        else
        {
            if( tip_rd_ack & i2c_ack_done )
            {
                if(i2c_data)
                    next_state = (STATE_IDLE);
                else
                    next_state = (STATE_READ);
            }
            else 
            {
                next_state = (STATE_READ_WAIT);
            }
        }
    }
    else
    {
        next_state = (STATE_IDLE);
    }

}


/*
* @fn  wishbone_address()
* 
* @details     Sets the wishbone address offset.
*/
void i2c_to_wb_if::wishbone_address()
{

    if( tip_addr_ack )
    {
        if(i2c_r_w_bit[0]== "1")
        {
            i2c_offset_r = 0;
        }
        else
        {
            i2c_offset_r = 8;
        }
    }
    else if( i2c_ack_done )
    {
        i2c_offset_r = i2c_offset_r + 1;
    }
}

/*
* @fn  byte_lane_select_1()
* 
* @details     Sets the wishbone output selector.
*/
void i2c_to_wb_if::byte_lane_select_1()
{
    switch(i2c_offset_r)
    {
        case 0:
            wb_sel_o.write(1);
            break;
        case 1:
            wb_sel_o.write(2);
            break;
        case 2:
            wb_sel_o.write(3);
            break;
        case 3:
            wb_sel_o.write(4);
            break;
    }
}

/*
* @fn  byte_lane_select_2()
* 
* @details     Sets the wishbone address offset.
*/
void i2c_to_wb_if::byte_lane_select_2()
{
    i2c_byte_out.write(wb_data_i.read().range(0,7));
    
    if(wb_sel_o.read() == "00")
    {
        i2c_byte_out.write(wb_data_i.read().range(0,7));
    }
    if(wb_sel_o.read() == "01")
    {
        i2c_byte_out.write(wb_data_i.read().range(8,15));
    }
    if(wb_sel_o.read() == "10")
    {
        i2c_byte_out.write(wb_data_i.read().range(16,23));
    }
    if(wb_sel_o.read() == "11")
    {
        i2c_byte_out.write(wb_data_i.read().range(24,31));
    }
}

/*
* @fn  assignSignal()
* 
* @details     Assign the outputs.
*/
void i2c_to_wb_if::assignSignal()
{
    if(state.read() == STATE_READ)
    {
        i2c_parallel_load.write(1);
    }
    else
    {
        i2c_parallel_load.write(0);
    }

    wb_addr_o.write(i2c_offset_r);
    sc_bv<32> tmp = (i2c_byte_in.read(), i2c_byte_in.read(), i2c_byte_in.read(), i2c_byte_in.read());
    wb_data_o.write (tmp);

    if(state.read() == STATE_WRITE || state.read() == STATE_READ)
    {
        wb_cyc_o.write(1);
        wb_stb_o.write(1);
    }
    else
    {
        wb_cyc_o.write(0);
        wb_stb_o.write(0);
    }

    if(state.read() == STATE_WRITE)
    {
        wb_we_o.write(1);
    }
    else
    {
        wb_we_o.write(0);
    }
    
}
