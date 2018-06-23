#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf i2c_to_wb_fsm.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 i2c_to_wb_fsm_tb.cpp i2c_to_wb_fsm.cpp  -lsystemc -lm -o i2c_to_wb_fsm.o
echo 'Simulation Started'
./i2c_to_wb_fsm.o
echo 'Simulation Ended'
