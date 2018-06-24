#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf i2c_master_model.o i2c_master_model.vcd
export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 tb_i2c_master_model.cpp i2c_master_model.cpp -lsystemc -lm -o i2c_master_model.o
echo 'Simulation Started'
./i2c_master_model.o
echo 'Simulation Ended'
