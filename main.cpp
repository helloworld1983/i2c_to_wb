#include "systemc.h"

int sc_main (int, char *[]) {
   
   sc_start();
   sc_signal<sc_logic> test;
   return 0;
}