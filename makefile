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


model: tb_dut.h glitch_generator.o wb_slave_model.o i2c_master_model.o
	$(CXX) $(CXXFLAGS) Model/tb_model.cpp tb_dut.h -o model.out \
	glitch_generator.o wb_slave_model.o i2c_master_model.o $(LDLIBS)

test_glitch_gen:Model/tb_glitch_generator.cpp glitch_generator.o
	$(CXX) $(CXXFLAGS) Model/tb_glitch_generator.cpp -o glitch_generator.out glitch_generator.o $(LDLIBS)
	./glitch_generator.out
	gtkwave glitch_generator.vcd
glitch_generator.o: Model/glitch_generator.cpp Model/glitch_generator.h
	$(CXX) $(CXXFLAGS) -c Model/glitch_generator.cpp Model/glitch_generator.h $(LDLIBS)
test_wb_wlave:Model/tb_wb_slave_model.cpp wb_slave_model.o
	$(CXX) $(CXXFLAGS) Model/tb_wb_slave_model.cpp -o wb_slave_model.out wb_slave_model.o $(LDLIBS)
	./wb_slave_model.out
	gtkwave wb_slave_model.vcd
wb_slave_model.o: Model/wb_slave_model.cpp Model/wb_slave_model.h
	$(CXX) $(CXXFLAGS) -c Model/wb_slave_model.cpp Model/wb_slave_model.h $(LDLIBS)
test_i2c_master: Model/tb_i2c_master_model.cpp i2c_master_model.o
	$(CXX) $(CXXFLAGS) Model/tb_i2c_master_model.cpp -o i2c_master_model.out i2c_master_model.o $(LDLIBS)
	./i2c_master_model.out
	gtkwave i2c_master_model.vcd
i2c_master_model.o: Model/i2c_master_model.cpp Model/i2c_master_model.h
	$(CXX) $(CXXFLAGS) -c Model/i2c_master_model.cpp Model/i2c_master_model.h $(LDLIBS)

test_glitch_filter: glitch_filter.o
	$(CXX) $(CXXFLAGS) tb_glitch_filter.cpp glitch_filter.o $(LDLIBS) -o glitch_filter.out
	./glitch_filter.out
	gtkwave -a glitch_filter_config.gtkw ./glitch_filter.vcd
glitch_filter.o: glitch_filter.cpp
	$(CXX) $(CXXFLAGS) -c glitch_filter.cpp $(LDLIBS)

test_fsm:i2c_to_wb_fsm/tb_i2c_to_wb_fsm.cpp i2c_to_wb_fsm.o
	$(CXX) $(CXXFLAGS) i2c_to_wb_fsm/tb_i2c_to_wb_fsm.cpp -o fsm.out i2c_to_wb_fsm.o $(LDLIBS)
i2c_to_wb_fsm.o: i2c_to_wb_fsm/i2c_to_wb_fsm.cpp
	$(CXX) $(CXXFLAGS) -c i2c_to_wb_fsm/i2c_to_wb_fsm.cpp $(LDLIBS)

test_if:i2c_to_wb_if/tb_i2c_to_wb_if.cpp i2c_to_wb_if.o
	$(CXX) $(CXXFLAGS) i2c_to_wb_if/tb_i2c_to_wb_if.cpp -o if.out i2c_to_wb_if.o $(LDLIBS)
i2c_to_wb_if.o: i2c_to_wb_if/i2c_to_wb_if.cpp i2c_to_wb_if/i2c_to_wb_if.h
	$(CXX) $(CXXFLAGS) -c i2c_to_wb_if/i2c_to_wb_if.cpp i2c_to_wb_if/i2c_to_wb_if.h $(LDLIBS)

test_config:i2c_to_wb_config/tb_i2c_to_wb_config.cpp i2c_to_wb_config.o
	$(CXX) $(CXXFLAGS) i2c_to_wb_config/tb_i2c_to_wb_config.cpp -o config.out i2c_to_wb_config.o $(LDLIBS)
i2c_to_wb_config.o: i2c_to_wb_config/i2c_to_wb_config.cpp i2c_to_wb_config/i2c_to_wb_config.h
	$(CXX) $(CXXFLAGS) -c i2c_to_wb_config/i2c_to_wb_config.cpp i2c_to_wb_config/i2c_to_wb_config.h $(LDLIBS)

clean:
	rm -f $(OUT_FILES)
