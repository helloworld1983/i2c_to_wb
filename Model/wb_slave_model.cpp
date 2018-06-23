    // Project: I2C to WishBone in SystemC
    // File: wb_slave_model.cpp
    // Autor: Diego Herrera
    // ITCR 2018


#include "wb_slave_model.h"

void wb_slave_model::ackDelayed()
{

}


void wb_slave_model::dataGen()
{
    uint memAddress = 0;

    if (we_i & cyc_i & stb_i & sel_i[0]) 
    {
        memAddress = static_cast< sc_uint >( data_in->read().range(AWIDTH-1,2) );
        cout<<"test"<<memAddress<<endl;
        //ram[{adr_i[AWIDTH-1:2], 2'b00'}] <= dat_i[7:0];
    }
        
        

    // if (we_i & cyc_i & stb_i & sel_i[1]) 
    //     ram[{adr_i[AWIDTH-1:2], 2'b01'}] <= dat_i[15:8];
        
    // always @ (posedge clk_i)
    // if (we_i & cyc_i & stb_i & sel_i[2]) 
    //     ram[{adr_i[AWIDTH-1:2], 2'b10'}] <= dat_i[23:16];
        
    // always @ (posedge clk_i)
    // if (we_i & cyc_i & stb_i & sel_i[3]) 
    //     ram[{adr_i[AWIDTH-1:2], 2'b11'}] <= dat_i[31:24];
        
    // assign dat_o = { ram[{adr_i[AWIDTH-1:2], 2'b11'}], ram[{adr_i[AWIDTH-1:2], 2'b10'}], ram[{adr_i[AWIDTH-1:2], 2'b01'}], ram[{adr_i[AWIDTH-1:2], 2'b00'}] };
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