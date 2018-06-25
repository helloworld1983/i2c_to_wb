// Project: I2C to WishBone in SystemC
// File: i2c_to-wb_fsm.h 
// Autor: Fernando Paris K.
// ITCR 2018

#ifndef I2C_TO_WB_FSM_H
#define I2C_TO_WB_FSM_H

#include <systemc.h>
#include <stdlib.h>

// FSM states enum
enum fsm_state
{
    idle,
    addr_byte,
    addr_ack,
    write,
    wr_ack,
    read,
    rd_ack,
    error
};

SC_MODULE(i2c_to_wb_fsm)
{
    // dbg aux
    //sc_in<fsm_state> nxt_st;

    // inputs
    sc_in<bool> i2c_data;
    sc_in<bool> i2c_data_rise;//
    sc_in<bool> i2c_data_fall;//
    sc_in<bool> i2c_clk;//
    sc_in<bool> i2c_clk_rise;
    sc_in<bool> i2c_clk_fall;
    sc_in<bool> i2c_r_w_bit;
    sc_in<bool> i2c_ack_out;

    sc_in<bool> wb_clk_i;//
    sc_in<bool> wb_rst_i;//

    // outputs
    sc_out<bool> i2c_ack_done;
    sc_out<bool> tip_addr_byte;
    sc_out<bool> tip_read_byte;
    sc_out<bool> tip_write_byte;
    sc_out<bool> tip_wr_ack;
    sc_out<bool> tip_rd_ack;
    sc_out<bool> tip_addr_ack;
    sc_out<bool> i2c_error;

    sc_out<sc_bv<8>> state_out;

    // internal signals
    sc_signal<fsm_state> state;
    sc_signal<fsm_state> next_state;
    sc_signal<sc_int<4>> bit_count;
    sc_signal<bool> xmt_byte_done;
    sc_signal<bool> tip_ack;
    sc_signal<bool> start_detected;
    sc_signal<bool> stop_detected;

    // methods
    void startDect();
    void stopDect();
    void nextStateCalc();
    void stateDeco();
    void byteDone();
    void byteDoneCntr();
    void tipAck();
    void i2cAckDone();
    void fsm();
    void tipAddrByte();
    void tipAddrAck();
    void tipReadByte();
    void tipWriteByte();
    void tipWrAck();
    void tipRdAck();
    void i2cError();

    // constructor
    SC_CTOR(i2c_to_wb_fsm)
    {
        SC_METHOD(startDect);
            sensitive << i2c_clk;
            sensitive << i2c_data_fall;
        
        SC_METHOD(stopDect);
            sensitive << i2c_clk;
            sensitive << i2c_data_rise;

        SC_METHOD(nextStateCalc);
            sensitive << wb_clk_i.pos();
            sensitive << wb_rst_i.pos();

        SC_METHOD(stateDeco);
            sensitive << state;

        SC_METHOD(byteDone);
            sensitive << bit_count;
            sensitive << i2c_clk_rise;

        SC_METHOD(tipAck);
            sensitive << bit_count;

        SC_METHOD(byteDoneCntr);
            sensitive << wb_clk_i.pos();

        SC_METHOD(i2cAckDone);
            sensitive << tip_ack;
            sensitive << i2c_clk_rise;

        SC_METHOD(fsm);
            sensitive << state;
            sensitive << start_detected;
            sensitive << xmt_byte_done;
            sensitive << stop_detected;
            sensitive << i2c_ack_out;
            sensitive << i2c_ack_done;
            sensitive << i2c_data;
            sensitive << i2c_r_w_bit;

        SC_METHOD(tipAddrByte);
            sensitive << state;

        SC_METHOD(tipAddrAck);
            sensitive << state;  

        SC_METHOD(tipReadByte);
            sensitive << state;

        SC_METHOD(tipWriteByte);
            sensitive << state;
            sensitive << tip_addr_byte;    
  
        SC_METHOD(tipWrAck);
            sensitive << state;
            sensitive << tip_addr_ack;   

        SC_METHOD(tipRdAck);
            sensitive << state;   

        SC_METHOD(i2cError);
            sensitive << state;                                         
    }   
};
#endif
