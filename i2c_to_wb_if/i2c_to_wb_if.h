#include <systemc.h>

typedef sc_bv<32> DW; 
typedef sc_bv<8> AW;




SC_MODULE(i2c_to_wb_if)
{
    sc_in<bool>        i2c_data;
    sc_in<bool>        i2c_ack_done;
    sc_in< AW >          i2c_byte_in;
    sc_out< AW >         i2c_byte_out;
    sc_out<bool>       i2c_parallel_load;
    sc_in<bool>        tip_wr_ack;
    sc_in<bool>        tip_rd_ack;
    sc_in<bool>       tip_addr_ack;

    sc_in<DW>          wb_data_i;
    sc_out<DW>         wb_data_o;
    sc_out<AW>         wb_addr_o;
    sc_out< sc_bv<2> >  wb_sel_o;
    sc_out<bool>       wb_we_o;
    sc_out<bool>       wb_cyc_o;
    sc_out<bool>       wb_stb_o;
    sc_in<bool>        wb_ack_i;
    sc_in<bool>        wb_err_i; //Not used
    sc_in<bool>        wb_rty_i; //Not used

    sc_in_clk          wb_clk_i;
    sc_in<bool>         wb_rst_i;

    
    sc_bv<1> i2c_r_w_bit; 
    sc_int<8> i2c_offset_r;
    sc_inout <sc_int<8> > state;
    sc_inout<sc_int<8> > next_state;
    

    void fsm_main(void);
    void fsm_aux(void);
    void getfirstbit(void);
    void wishbone_address(void);
    void byte_lane_select_1(void);
    void byte_lane_select_2(void);
    void assignSignal(void);


    SC_CTOR(i2c_to_wb_if)
    {

        SC_METHOD(fsm_main);
        sensitive << wb_clk_i.pos() << wb_rst_i.pos();

        SC_METHOD(fsm_aux);
        sensitive << wb_clk_i.pos() << wb_rst_i.pos() << i2c_data << i2c_ack_done << tip_wr_ack << tip_rd_ack << wb_data_i << wb_ack_i;

        SC_METHOD(getfirstbit);
        sensitive << i2c_byte_in;
        
        SC_METHOD(wishbone_address);
        sensitive << wb_clk_i.pos();

        SC_METHOD(byte_lane_select_1);
        sensitive << wb_clk_i.pos() << wb_rst_i.pos() << i2c_data << i2c_ack_done << tip_wr_ack << tip_rd_ack << wb_data_i << wb_ack_i; 

        SC_METHOD(byte_lane_select_2);
        sensitive << wb_clk_i.pos() << wb_rst_i.pos() << i2c_data << i2c_ack_done << tip_wr_ack << tip_rd_ack << wb_data_i << wb_ack_i;

        SC_METHOD(assignSignal);
        sensitive << wb_clk_i.pos() << wb_rst_i.pos() << i2c_data << i2c_ack_done << tip_wr_ack << tip_rd_ack << wb_data_i << wb_ack_i;
        
    }



};
