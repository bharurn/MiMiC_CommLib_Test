LDFLAGS= ../../lib/lib/libmimiccomm.a -lm
COMM_LIB = ../../src/
SOURCES = test2.cpp
CXX = mpicxx
CXXFLAGS = -std=c++11 -Wno-write-strings -I$(COMM_LIB) -cxx=icpc

test1: test2.cpp ../../lib/lib/libmimiccomm.a
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o test2.a
