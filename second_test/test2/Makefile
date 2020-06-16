LDFLAGS= /home/mk115227/tests/CommLib/lib/lib/libmimiccomm.a -lm
COMM_LIB = /home/mk115227/tests/CommLib/src
SOURCES = test2.cpp
CXX = mpiicpc
CXXFLAGS = -std=c++11 -Wno-write-strings -I$(COMM_LIB)

test1: test2.cpp /home/mk115227/tests/CommLib/lib/lib/libmimiccomm.a
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o test2
