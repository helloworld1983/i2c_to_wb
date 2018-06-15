# ITCR - Diego Herrera
ARCH=$(shell getconf LONG_BIT)
SYSCDIR=/usr/local/systemc-2.3.2
LDFLAGS_32= -L$(SYSCDIR)/lib-linux -lsystemc -lm
LDFLAGS_64= -L$(SYSCDIR)/lib-linux64 -lsystemc -lm
LDFLAGS=$(LDFLAGS_$(ARCH))
CXXFLAGS=-Wno-deprecated -I$(SYSCDIR)/include

all:
	g++ $(CXXFLAGS) main.cpp $(LDFLAGS) -o i2c_to_wb.out