# ITCR - Diego Herrera
ARCH=$(shell getconf LONG_BIT)
SYSCDIR=/usr/local/systemc-2.3.2
LDLIBS_32= -L$(SYSCDIR)/lib-linux -lsystemc -lm
LDLIBS_64= -L$(SYSCDIR)/lib-linux64 -lsystemc -lm
LDLIBS=$(LDLIBS_$(ARCH))
CXXFLAGS=-Wno-deprecated -I$(SYSCDIR)/include
CXX=g++

OUT_FILES=glitch_filter.o glitch_filter.vcd

all: glitch_filter.o
	$(CXX) $(CXXFLAGS) main.cpp glitch_filter.o $(LDLIBS) -o i2c_to_wb.o

glitch_filter.o: glitch_filter.cpp
	$(CXX) $(CXXFLAGS) -c glitch_filter.cpp $(LDLIBS)

test_glitch_filter: 
	$(CXX) $(CXXFLAGS) tb_glitch_filter.cpp glitch_filter.cpp $(LDLIBS) -o glitch_filter.o
	./glitch_filter.o
	gtkwave -a glitch_filter_config.gtkw ./glitch_filter.vcd

clean:
	rm -f $(OUT_FILES)
