# ITCR - Diego Herrera
ARCH=$(shell getconf LONG_BIT)
SYSCDIR=/usr/local/systemc-2.3.2
LDLIBS_32= -L$(SYSCDIR)/lib-linux -lsystemc -lm
LDLIBS_64= -L$(SYSCDIR)/lib-linux64 -lsystemc -lm
LDLIBS=$(LDLIBS_$(ARCH))
CXXFLAGS=-Wno-deprecated -I$(SYSCDIR)/include
CXX=g++

OUT_FILES=*.o *.out *.vcd

all: glitch_generator.o glitch_filter.o
	$(CXX) $(CXXFLAGS) main.cpp glitch_generator.o $(LDLIBS) -o i2c_to_wb.out

modelrun: model
	./model
model: glitch_generator.o wb_slave_model.o
	$(CXX) $(CXXFLAGS) Model/tb_model.cpp -o model.out glitch_generator.o wb_slave_model.o $(LDLIBS)

testGlitchGen:Model/tb_glitch_generator.cpp glitch_generator.o
	$(CXX) $(CXXFLAGS) Model/tb_glitch_generator.cpp -o testGlitchGen.out glitch_generator.o $(LDLIBS)
glitch_generator.o: Model/glitch_generator.cpp Model/glitch_generator.h
	$(CXX) $(CXXFLAGS) -c Model/glitch_generator.cpp Model/glitch_generator.h $(LDLIBS)
testWbSlave:Model/tb_wb_slave_model.cpp wb_slave_model.o
	$(CXX) $(CXXFLAGS) Model/tb_wb_slave_model.cpp -o testWbSlave.out wb_slave_model.o $(LDLIBS)
wb_slave_model.o: Model/wb_slave_model.cpp Model/wb_slave_model.h
	$(CXX) $(CXXFLAGS) -c Model/wb_slave_model.cpp Model/wb_slave_model.h $(LDLIBS)


glitch_filter.o: glitch_filter.cpp
	$(CXX) $(CXXFLAGS) -c glitch_filter.cpp $(LDLIBS)
test_glitch_filter: glitch_filter.o
	$(CXX) $(CXXFLAGS) tb_glitch_filter.cpp glitch_filter.o $(LDLIBS) -o glitch_filter.out
	./glitch_filter.out
	gtkwave -a glitch_filter_config.gtkw ./glitch_filter.vcd

clean:
	rm -f $(OUT_FILES)
