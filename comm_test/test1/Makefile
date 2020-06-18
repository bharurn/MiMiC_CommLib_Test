LDFLAGS= ../../lib/lib/libmimiccomm.a -lm
COMM_LIB = ../../src/
SOURCES = test1.cpp
CXX = mpicxx
CXXFLAGS = -std=c++11 -Wno-write-strings -I$(COMM_LIB)

test1: test1.cpp ../../lib/lib/libmimiccomm.a
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o test1
