#include "i2c_to_wb_fsm.h"

// aux members
int aux_cntr = 0;

// sets next state
void i2c_to_wb_fsm::nextStateCalc()
{
    if(wb_rst_i)
    {
        state.write(fsm_state::idle);
    }
    else
    {
        state.write(next_state);
    }
}


// sets start_detected signal
void i2c_to_wb_fsm::startDect()
{
    start_detected.write(i2c_data_fall.read() & i2c_clk.read());
}


// sets stop_detected signal
void i2c_to_wb_fsm::stopDect()
{
    stop_detected.write(i2c_data_rise.read() & i2c_clk.read());
}


// byte done indicator circuit
void i2c_to_wb_fsm::byteDone()
{
    xmt_byte_done.write(i2c_clk_rise.read() & (bit_count.read()==7));
}

// tip_ack
void i2c_to_wb_fsm::tipAck()
{
    tip_ack.write((bit_count.read()==8));
}


// byte done logic counter
void i2c_to_wb_fsm::byteDoneCntr()
{
    if(wb_rst_i || i2c_ack_done || start_detected)
    {
        bit_count = 4;
        aux_cntr = 4;
    }
    else if(i2c_clk_fall)
    {
        aux_cntr++;
        bit_count = aux_cntr;
    }
}


// i2c_ack_done
void i2c_to_wb_fsm::i2cAckDone()
{
    i2c_ack_done.write(tip_ack & i2c_clk_rise);
}

// converts fsm_state enum to bit vecto ("b000000)
void i2c_to_wb_fsm::fsm()
{
    switch(state)
    {
        case fsm_state::idle:
        {
            if( start_detected.read() )
            {
                next_state.write(fsm_state::addr_byte);
            }
            else
            {
                next_state.write(fsm_state::idle);
            }
            break;
        }
        case fsm_state::addr_byte:
        {
            if( xmt_byte_done.read() )
            {
               next_state.write(fsm_state::addr_ack);
            }
            else if (stop_detected.read())
            {
               next_state.write(fsm_state::error);
            }
            else
            {
               next_state.write(fsm_state::addr_byte);
            }
            break;
        }
        case fsm_state::addr_ack:
        {
            if( i2c_ack_out.read() )
            {
               next_state.write(fsm_state::idle);
            }
            else if(i2c_ack_done.read())
            {
                if (i2c_r_w_bit.read())
                {
                   next_state.write(fsm_state::read);
                }
                else
                {
                   next_state.write(fsm_state::write);
                }
            }
            else if (start_detected.read() || stop_detected.read())
            {
               next_state.write(fsm_state::error);
            }
            else
            {
               next_state.write(fsm_state::addr_ack);
            }
            break;
        }
        case fsm_state::write:
        {
            if( xmt_byte_done.read() )
            {
               next_state.write(fsm_state::wr_ack);
            }
            else if(start_detected)
            {
               next_state.write(fsm_state::addr_byte);
            }
            else if (stop_detected.read())
            {
               next_state.write(fsm_state::idle);
            }
            else
            {
               next_state.write(fsm_state::write);
            }
            break;
        }
        case fsm_state::wr_ack:
        {
            if( i2c_ack_done.read() )
            {
               next_state.write(fsm_state::write);
            }
            else if( start_detected.read() || stop_detected.read() )
            {
               next_state.write(fsm_state::error);
            }
            else
            {
               next_state.write(fsm_state::wr_ack);
            }
            break;
        }
        case fsm_state::read:
        {
            if( xmt_byte_done.read() )
            {
               next_state.write(fsm_state::rd_ack);
            }
            else if(start_detected.read())
            {
               next_state.write(fsm_state::addr_byte);
            }
            else if(stop_detected.read())
            {
               next_state.write(fsm_state::idle);
            }
            else
            {
               next_state.write(fsm_state::read);
            }
            break;
        }
        case fsm_state::rd_ack:
        {
            if( i2c_ack_done.read() )
            {
                if (i2c_data.read())
                {
                   next_state.write(fsm_state::idle);
                }
                else
                {
                   next_state.write(fsm_state::read);
                } 
            }
            else if (start_detected.read() || stop_detected.read())
            {
               next_state.write(fsm_state::error);
            }
            else
            {
               next_state.write(fsm_state::rd_ack);
            }
            break;
        }
        case fsm_state::error:
        {
           next_state.write(fsm_state::idle);
            break;
        }
        default:
        {
           next_state.write(fsm_state::error);
            break;            
        }                                                         
    }
}


// tip_addr_byte
void i2c_to_wb_fsm::tipAddrByte()
{
    tip_addr_byte.write(state == fsm_state::addr_byte);
}


// tip_addr_ack
void i2c_to_wb_fsm::tipAddrAck()
{
    tip_addr_ack.write(state == fsm_state::addr_ack);
}


// tip_read_byte
void i2c_to_wb_fsm::tipReadByte()
{
    tip_read_byte.write(state == fsm_state::read);
}

// tip_write_byte
void i2c_to_wb_fsm::tipWriteByte()
{
    tip_write_byte.write((state == fsm_state::write) || tip_addr_byte);
}


// tip_wr_ack
void i2c_to_wb_fsm::tipWrAck()
{
    tip_wr_ack.write((state == fsm_state::wr_ack) || tip_addr_ack);
}


// tip_rd_ack
void i2c_to_wb_fsm::tipRdAck()
{
    tip_rd_ack.write(state == fsm_state::rd_ack);
}


// i2c_error
void i2c_to_wb_fsm::i2cError()
{
    i2c_error.write(state == fsm_state::error); //|| i2c_start_error);
}

// converts fsm_state enum to bit vector ("b000000)
void i2c_to_wb_fsm::stateDeco()
{
    switch(state)
    {
        case fsm_state::idle:
        {
            state_out.write("00000001");
            break;
        }
        case fsm_state::addr_byte:
        {
            state_out.write("00000010");
            break;
        }
        case fsm_state::addr_ack:
        {
            state_out.write("00000100");
            break;
        }
        case fsm_state::write:
        {
            state_out.write("00001000");
            break;
        }
        case fsm_state::wr_ack:
        {
            state_out.write("00010000");
            break;
        }
        case fsm_state::read:
        {
            state_out.write("00100000");
            break;
        }
        case fsm_state::rd_ack:
        {
            state_out.write("01000000");
            break;
        }
        case fsm_state::error:
        {
            state_out.write("10000000");
            break;
        }
        default:
        {
            state_out.write("00000001");
            break;            
        }                                                         
    }  
}


// debug function, dump internal signals
void i2c_to_wb_fsm::tracing(sc_trace_file *tf)
{
    const std::string str = this->name();

    // Dump input signals
    sc_trace(tf, this->i2c_data, str+".i2c_data");
    sc_trace(tf, this->i2c_data_rise, str+".i2c_data_rise");
    sc_trace(tf, this->i2c_data_fall, str+".i2c_data_fall");
    sc_trace(tf, this->i2c_clk, str+".i2c_clk");
    sc_trace(tf, this->i2c_clk_rise, str+".i2c_clk_rise");
    sc_trace(tf, this->i2c_clk_fall, str+".next_state");
    sc_trace(tf, this->i2c_r_w_bit, str+".i2c_r_w_bit");  
    sc_trace(tf, this->i2c_ack_out, str+".i2c_ack_out");
    sc_trace(tf, this->wb_clk_i, str+".wb_clk_i");
    sc_trace(tf, this->wb_rst_i, str+".wb_rst_i");

    // Dump local signals
    sc_trace(tf, this->start_detected, str+".start_detected");
    sc_trace(tf, this->stop_detected, str+".stop_detected");
    sc_trace(tf, this->tip_ack, str+".tip_ack");
    sc_trace(tf, this->xmt_byte_done, str+".xmt_byte_done");
    sc_trace(tf, this->state, str+".state");
    sc_trace(tf, this->next_state, str+".next_state");
    sc_trace(tf, this->bit_count, str+".bit_count");

    // Dump output signals
    sc_trace(tf, this->i2c_ack_done, str+".i2c_ack_done");
    sc_trace(tf, this->tip_addr_byte, str+".tip_addr_byte");
    sc_trace(tf, this->tip_read_byte, str+".tip_read_byte");
    sc_trace(tf, this->tip_write_byte, str+".tip_write_byte");
    sc_trace(tf, this->tip_wr_ack, str+".tip_wr_ack");
    sc_trace(tf, this->tip_rd_ack, str+".tip_rd_ack");
    sc_trace(tf, this->tip_addr_ack, str+".tip_addr_ack");  
    sc_trace(tf, this->i2c_error, str+".i2c_error");
    sc_trace(tf, this->state_out, str+".state_out");       
}
