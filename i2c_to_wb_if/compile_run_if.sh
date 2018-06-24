#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf i2c_to_wb_if.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 i2c_to_wb_if.h i2c_to_wb_if.cpp main.cpp -lsystemc -lm -o i2c_to_wb_if.o
echo 'Simulation Started'
./i2c_to_wb_if.o
echo 'Simulation Ended'
