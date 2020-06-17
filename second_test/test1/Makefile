LDFLAGS= ../../lib/lib/libmimiccomm.a -lm#/p/home/jusers/raghavan1/jureca/MiMiC_CommLib_Test/lib/lib/libmimiccomm.a -lm
COMM_LIB = ../../src/#/p/home/jusers/raghavan1/jureca/MiMiC_CommLib_Test/src/
SOURCES = test1.cpp
CXX = mpicxx
CXXFLAGS = -std=c++11 -Wno-write-strings -I$(COMM_LIB)

test1: test1.cpp ../../lib/lib/libmimiccomm.a #/p/home/jusers/raghavan1/jureca/MiMiC_CommLib_Test/lib/lib/libmimiccomm.a
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o test1
