#include "systemc.h"

// Define Contants
#define tBUF     4700
#define tSU_STA  4700
#define tSU_DAT  250
#define tHD_DAT  300
#define tHD_STA  4000 
#define tLOW     4700
#define tHIGH    4000

// Define Module
SC_MODULE (i2c_master_model) 
{
    // -----------------------------------------> Ports Definition
    sc_in<bool>         i2c_clk;
    sc_inout<bool>      i2c_data;
    // WriteByte Task
    sc_in< sc_bv<8> >   task_write_byte_arg;
    sc_in<bool>         task_write_byte_trigger;
    // ReadByte Task
    sc_in<int>          task_read_byte_arg;
    sc_in<bool>         task_read_byte_trigger;
    // Start Task
    sc_in<bool>         task_start_trigger;
    // Stop Task
    sc_in<bool>         task_stop_trigger;
    
    // -----------------------------------------> Variables
    // Wires
    sc_bv<1>    i2c_clk_in;
    sc_bv<1>    i2c_data_in;

    // Reg
    sc_bv<1>    i2c_data_oe;
    sc_bv<1>    i2c_clk_oe;
    sc_bv<1>    i2c_data_out;
    sc_bv<1>    i2c_clk_out;
    sc_bv<1>    i2c_ack_in;
    
    // Tasks
    sc_bv<1>    start_r;
    sc_bv<1>    write_byte_r;
    sc_bv<8>    i2c_buffer_in;

    // -----------------------------------------> Methods
    // Define C++ Methods
    void tracing(sc_trace_file *tf);

    // Define SystemC Methods
    void initial();
    void start();
    void stop();
    void write_byte();
    void read_byte();
    void wiresAndAssigns();
    
    // Constructor
    SC_CTOR(i2c_master_model)
    {
        SC_THREAD(write_byte);
            sensitive << task_write_byte_trigger;

        SC_THREAD(read_byte);
            sensitive << task_read_byte_trigger;
        
        SC_METHOD(wiresAndAssigns);
            sensitive << i2c_clk;
            sensitive << i2c_data;

        SC_THREAD(start);
            sensitive << task_start_trigger;
        
        SC_THREAD(stop);
            sensitive << task_stop_trigger;
    }
    
};  // End of Module
