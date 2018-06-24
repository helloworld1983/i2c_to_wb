    // Project: I2C to WishBone in SystemC
    // File: wb_slave_model.cpp
    // Autor: Diego Herrera
    // ITCR 2018


#include "wb_slave_model.h"

void wb_slave_model::ackDelayed()
{
    err_o.write(0);
    rty_o.write(0);
    sc_bit ack;
    
    cout<<"Ack Delayed"<<endl;
    while(true)
    {
        if (cyc_i && stb_i)
        {            
            ack = 0;
            ack_o.write(ack);
            
            wait();
            wait();
            if (cyc_i && stb_i)
            {            
                ack = 1;
            }
            else
            {
                ack = 0;
            }
        }
        else
        {
            ack = 0;
        }

        ack_o.write(ack);
        wait();
    }
}

void wb_slave_model::setOutData()
{    
    uint memAddress;
    sc_uint<DWIDTH> data_out;
    sc_uint<DWIDTH> address_in;

    memAddress = (address_in.range(AWIDTH-1,2)<<2);

    // data_out.range(7,0) =  ram[memAddress];
    // data_out.range(15,8) =  ram[memAddress & 1];
    // data_out.range(23,16) =  ram[memAddress & 2];
    // data_out.range(31,24) =  ram[memAddress & 3];

    data_out=(ram[memAddress & 3],ram[memAddress & 2],ram[memAddress & 1],ram[memAddress]);
    dat_o.write(data_out) ; 

    // cout<<"Out - Address : "<<address_in<<endl;
    // cout<<"Out - Memory Address : "<<memAddress<<endl;
    // cout<<"Out - Data: "<<data_out<<endl;         
}


void wb_slave_model::dataGen()
{
    uint memAddress;
    sc_uint<DWIDTH/8> sel_in;
    sc_uint<DWIDTH> data_in;
    sc_uint<DWIDTH> address_in;
    cout<<"Data Gen"<<endl;
    
    while(true)
    {
        sel_in = sel_i.read();
        data_in = dat_i.read();
        address_in = adr_i.read();

        if (we_i && cyc_i && stb_i && (sel_in[0]==1))
        {
            //ram[{adr_i[AWIDTH-1:2], 2'b00'}] <= dat_i[7:0];
            memAddress =  (address_in.range(AWIDTH-1,2)<<2)&0 ;
            ram[memAddress] = data_in.range(7,0);                              
        }

        if (we_i && cyc_i && stb_i && (sel_in[1]==1))
        {
            //ram[{adr_i[AWIDTH-1:2], 2'b00'}] <= dat_i[7:0];
            memAddress =  (address_in.range(AWIDTH-1,2)<<2)&1 ;
            ram[memAddress] = data_in.range(15,8);                              
        }

        if (we_i && cyc_i && stb_i && (sel_in[2]==1))
        {
            //ram[{adr_i[AWIDTH-1:2], 2'b00'}] <= dat_i[7:0];
            memAddress =  (address_in.range(AWIDTH-1,2)<<2)&2 ;
            ram[memAddress] = data_in.range(23,16);                              
        }

        if (we_i && cyc_i && stb_i && (sel_in[3]==1))
        {
            //ram[{adr_i[AWIDTH-1:2], 2'b00'}] <= dat_i[7:0];
            memAddress =  (address_in.range(AWIDTH-1,2)<<2)&3 ;
            ram[memAddress] = data_in.range(31,24);                              
        }

        // cout<<"Data In: "<<data_in<<endl;
        // cout<<"Memory Address : "<<memAddress<<endl;
        // cout<<"Memory Data: "<<ram[memAddress]<<endl;

        wait();
    }
}

void wb_slave_model::readMemory()
{    
    ifstream inputFile(SLAVE_RAM_INIT);        // Input file stream object

    // Check if exists and then open the file.
    if (inputFile.good()) {
        // Push items into a vector
        int memCell = 0;
        while (inputFile >> memCell){
            ram.push_back(memCell);
        }

        // Close the file.
        inputFile.close();

        // Display the data read:  
         cout << "The Memory data is: ";
        for (int count = 0; count < ram.size(); count++){
            cout << ram[count] << " ";
        }      

        cout << endl;
    }else {
        cout << "Error!";
        //_exit(0);
    }
}