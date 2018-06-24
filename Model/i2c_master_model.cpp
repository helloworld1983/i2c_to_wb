#include "i2c_master_model.h"

/*
* @fn  tracing()
* 
* @details     Function to add internal signal to 
*              VCD dump file
*/
void i2c_master_model::tracing(sc_trace_file *tf)
{
    cout << "INVOKED - "<< "tracing" << endl;
    const std::string str = this->name();
    
    // Dump local signals
    sc_trace(tf, this->i2c_data_oe, str+".i2c_data_oe");
    sc_trace(tf, this->i2c_clk_oe, str+".i2c_clk_oe");
    sc_trace(tf, this->i2c_data_out, str+".i2c_data_out");
    sc_trace(tf, this->i2c_clk_out, str+".i2c_clk_out");
    sc_trace(tf, this->i2c_data_in, str+".i2c_data_in");
    sc_trace(tf, this->i2c_clk_in, str+".i2c_clk_in");
    sc_trace(tf, this->i2c_ack_in, str+".i2c_ack_in");
    sc_trace(tf, this->start_r, str+".start_r");
    sc_trace(tf, this->task_write_byte_arg, str+".task_write_byte_arg");
    sc_trace(tf, this->write_byte_r, str+".write_byte_r");
    
    
}

/*
* @fn  initial()
* 
* @details     Mimic verilog "Initial" statement
*/
void i2c_master_model::initial()
{
    cout << "INVOKED - "<< "initial" << endl;
    
    // Regs
    i2c_data_oe   = 0;
    i2c_clk_oe    = 0;
    i2c_data_out  = 1;
    i2c_clk_out   = 1;

    // Tasks
    start_r       = 0;
    write_byte_r  = 0;
    i2c_buffer_in = 0;
}

/*
* @fn  wiresAndAssigns()
* 
* @details     SystemC method to mimic "always *"
*/
void i2c_master_model::wiresAndAssigns()
{
    //cout << "INVOKED - "<< "wiresAndAssigns" << endl;

    i2c_data_in = i2c_data;
    i2c_clk_in = i2c_clk;

    if (i2c_data_oe == 1)
    {
        i2c_data.write(i2c_data_out.get_bit(0));
    }
    else
    {
        i2c_data.write(0);                        ////// SHOULD BE HI-Z
    }

    // sc_clock only works with inputs, the module clock
    // is defined as an input, not as inout 
    /*
    if (i2c_clk_oe == 1)
    {
        i2c_clk.write(i2c_clk_out.get_bit(0));
    }
    else
    {
        i2c_clk.write(0);                         ////// SHOULD BE HI-Z
    }
    */
}

/*
* @fn  templateSystemcMethod()
* 
* @details     Stadard SystemC method
*/
void i2c_master_model::start()
{
    while (true)
    {
        wait();
        cout << "INVOKED - "<< "start" << endl;

        start_r = 1;

        wait(tBUF, SC_NS);

        if (i2c_data != 1)
        {
            if(i2c_clk != 0)
            {
                wait(tHIGH, SC_NS);
            }

            i2c_clk_out = 0;
            i2c_clk_oe  = 1;

            wait(tHD_DAT, SC_NS);
            i2c_data_out = 1;
            i2c_data_oe  = 1;
        }

        if(i2c_clk != 1)
        {
            wait(tLOW, SC_NS);
        }

        i2c_clk_out = 1;
        i2c_clk_oe  = 1;

        wait(tSU_STA, SC_NS);
        i2c_data_out = 0; 
        i2c_data_oe  = 1;

        start_r = 0;
    }
}

/*
* @fn  templateSystemcMethod()
* 
* @details     Stadard SystemC method
*/
void i2c_master_model::stop()
{
    while (true)
    {
        wait();
        cout << "INVOKED - "<< "stop" << endl;

        if(i2c_data != 0)
        {
            wait(tHD_DAT, SC_NS);
            i2c_data_out = 0;
        }
            
        if( i2c_clk != 1)
        {
            i2c_clk_out = 1;
            wait(tLOW, SC_NS);
        }

        i2c_data_out  = 1;
        i2c_clk_out   = 1;
            
        i2c_data_oe = 0;
        i2c_clk_oe  = 0;
    }
}

/*
* @fn  templateSystemcMethod()
* 
* @details     Stadard SystemC method
*/
void i2c_master_model::write_byte()
{
    while(true)
    {
        wait();
        cout << "INVOKED - "<< "write_byte" << endl;

        write_byte_r = 1;
        cout << "###- I2C write 0x" << task_write_byte_arg << endl;

        wait(tHD_STA, SC_NS);
        i2c_clk_out = 0;

        //---- white_bit
        sc_bv<8> tempBuffer = 0;
        for (int bit=7; bit>=0; bit--)
        {
            wait(tHD_DAT, SC_NS);
            i2c_data_oe = 1;
            tempBuffer = task_write_byte_arg;
            i2c_data_out = tempBuffer.get_bit(bit);

            cout << "###- I2C writing bit = " << i2c_data_out << " bit_position = " << bit << endl;

            wait(tLOW, SC_NS);
            i2c_clk_out = 1;
            
            wait(tHIGH, SC_NS);
            i2c_clk_out = 0;
        }
        //----

        wait(tHD_DAT,SC_NS);
        i2c_data_oe = 0;
        
        wait(tLOW,SC_NS);
        i2c_clk_out = 1;
        i2c_ack_in = i2c_data;

        if(i2c_data == 1)
        {
            cout << "###- I2C NACK!" << endl;
        }
        else
        {
            cout << "###- I2C ACK!" << endl;
        }
            
        wait(tHIGH,SC_NS);
        i2c_clk_out = 0;
        
        wait(tHD_DAT, SC_NS);
        i2c_data_oe = 1;
        
        wait(tLOW,SC_NS);
        write_byte_r = 0;
    }

}

/*
* @fn  templateSystemcMethod()
* 
* @details     Standard SystemC method
*/
void i2c_master_model::read_byte()
{
    while(true)
    {
        wait();
        cout << "INVOKED - "<< "taskReadByte" << endl;

        wait(tHD_STA, SC_NS);
            
        i2c_clk_out = 0;
        i2c_data_oe = 0;
        
        //---- read_bit
        for (int bit=7; bit>=0; bit--)
        {
            i2c_data_oe = 0;
            
            wait(tHD_DAT, SC_NS);
            i2c_buffer_in.set_bit(bit, i2c_data_in.get_bit(0));

            cout << "###- I2C reading bit = " << i2c_buffer_in << " bit_position = " << bit << endl;
            
            wait(tLOW, SC_NS);
            i2c_clk_out = 1;
            
            wait(tHIGH, SC_NS);
            i2c_clk_out = 0;

        }
        //----

        wait(tHD_DAT, SC_NS);
        i2c_data_out = task_read_byte_arg;
        i2c_data_oe = 1;
       
        wait((tLOW-tHD_DAT), SC_NS);
        i2c_clk_out = 1;
        
        cout << "###- I2C read 0x" << std::hex << i2c_buffer_in << endl;;

        wait(tHIGH, SC_NS);
        i2c_clk_out = 0;
        wait(tLOW, SC_NS);
    }
}
