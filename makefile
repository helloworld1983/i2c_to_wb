# ITCR - Diego Herrera
ARCH=$(shell getconf LONG_BIT)
SYSCDIR=/usr/local/systemc-2.3.2
LDLIBS_32= -L$(SYSCDIR)/lib-linux -lsystemc -lm
LDLIBS_64= -L$(SYSCDIR)/lib-linux64 -lsystemc -lm
LDLIBS=$(LDLIBS_$(ARCH))
CXXFLAGS=-Wno-deprecated -I$(SYSCDIR)/include
CXX=g++

all: 
	$(CXX) $(CXXFLAGS) main.cpp glitch_generator.cpp glitch_generator.h $(LDLIBS) -o i2c_to_wb.o

model: glitch_generator.o
	$(CXX) $(CXXFLAGS) main.cpp -o model glitch_generator.o $(LDLIBS)
glitch_generator.o: glitch_generator.cpp glitch_generator.h
	$(CXX) $(CXXFLAGS) -c glitch_generator.cpp glitch_generator.h $(LDLIBS)

clean:
	rm -f i2c_to_wb.o