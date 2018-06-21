# ITCR - Diego Herrera
ARCH=$(shell getconf LONG_BIT)
SYSCDIR=/usr/local/systemc-2.3.2
LDLIBS_32= -L$(SYSCDIR)/lib-linux -lsystemc -lm
LDLIBS_64= -L$(SYSCDIR)/lib-linux64 -lsystemc -lm
LDLIBS=$(LDLIBS_$(ARCH))
CXXFLAGS=-Wno-deprecated -I$(SYSCDIR)/include
CXX=g++

OUT_FILES=i2c_to_wb.o model model.vcd glitch_generator.o

all: glitch_generator.o
	$(CXX) $(CXXFLAGS) main.cpp glitch_generator.o $(LDLIBS) -o i2c_to_wb.o

modelrun: model
	./model
model: glitch_generator.o
	$(CXX) $(CXXFLAGS) Model/tb_model.cpp -o model glitch_generator.o $(LDLIBS)
glitch_generator.o: Model/glitch_generator.cpp Model/glitch_generator.h
	$(CXX) $(CXXFLAGS) -c Model/glitch_generator.cpp Model/glitch_generator.h $(LDLIBS)

clean:
	rm -f $(OUT_FILES)