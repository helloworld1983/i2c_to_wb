#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf glitch_filter.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 glitch_filter.cpp tb_glitch_filter.cpp  -lsystemc -lm -o glitch_filter.o
echo 'Simulation Started'
./glitch_filter.o
echo 'Simulation Ended'
