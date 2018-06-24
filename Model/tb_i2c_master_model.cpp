#include "systemc.h"
#include "i2c_master_model.h"

int sc_main (int argc, char* argv[]) 
{
  // Ports
  sc_clock i2c_clk("i2c_clk", 1, SC_NS, 0.5);
  sc_signal<bool>         i2c_data;
  // Triggers and arguments for the task
  sc_signal< sc_bv<8> >   task_write_byte_arg;
  sc_signal<bool>         task_write_byte_trigger;
  sc_signal<int>          task_read_byte_arg;
  sc_signal<bool>         task_read_byte_trigger;
  sc_signal<bool>         task_start_trigger;
  sc_signal<bool>         task_stop_trigger;

  
  // Module Instance
  i2c_master_model i2c_master_model_tb("i2c_master_model");
    i2c_master_model_tb.i2c_clk(i2c_clk);
    i2c_master_model_tb.i2c_data(i2c_data);
    i2c_master_model_tb.task_write_byte_arg(task_write_byte_arg);
    i2c_master_model_tb.task_write_byte_trigger(task_write_byte_trigger);
    i2c_master_model_tb.task_read_byte_arg(task_read_byte_arg);
    i2c_master_model_tb.task_read_byte_trigger(task_read_byte_trigger);
    i2c_master_model_tb.task_start_trigger(task_start_trigger);
    i2c_master_model_tb.task_stop_trigger(task_stop_trigger);


  // Open VCD file
  sc_trace_file *tf = sc_create_vcd_trace_file("i2c_master_model");
  tf->set_time_unit(1, SC_PS);
  
  // Dump the desired signals
  sc_trace(tf, i2c_clk, "i2c_clk");
  sc_trace(tf, i2c_data, "i2c_data");
  sc_trace(tf, task_write_byte_arg, "task_write_byte_arg");
  sc_trace(tf, task_write_byte_trigger, "task_write_byte_trigger");
  sc_trace(tf, task_read_byte_arg, "task_read_byte_arg");
  sc_trace(tf, task_read_byte_trigger, "task_read_byte_trigger");
  sc_trace(tf, task_start_trigger, "task_start_trigger");
  sc_trace(tf, task_stop_trigger, "task_stop_trigger");
  // Dump internal signals
  i2c_master_model_tb.tracing(tf);

  // ------------------------------------------------------------
  cout << "@" << sc_time_stamp() <<" Start simulation\n" << endl;
  
    // Initial
    i2c_master_model_tb.initial();

    // Trigger Write Byte
    sc_start(10,SC_NS);
    i2c_data = 0;
    task_start_trigger = 1;                       // Start ---
    // Trigger Write Byte
    sc_start(10,SC_NS);
    task_write_byte_arg = "00000011";             // 0x03
    task_write_byte_trigger = 1;                  // Write Byte

    sc_start(90000,SC_NS);  
    task_stop_trigger = 1;                        // Stop  ***
    
    sc_start(10,SC_NS);  
    task_start_trigger = 0;                       // Start ---

    task_read_byte_arg = 1;                       // ACK
    task_read_byte_trigger = 1;                   // Read Byte

    sc_start(90000,SC_NS);
    task_stop_trigger = 0;                        // Stop  ***
    
    sc_start(10,SC_NS);  

  
  cout << "@" << sc_time_stamp() <<" End simulation\n" << endl;
  sc_close_vcd_trace_file(tf);

  return 0; // Terminate simulation
 }
