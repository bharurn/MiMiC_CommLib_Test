cmake_minimum_required(VERSION 3.3)
project(MimicCommLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Message.h transport/SocketTransport.cpp transport/SocketTransport.h transport/Transport.h MessageService.cpp MessageService.h JsonSerializer.cpp JsonSerializer.h Serializer.h)
add_executable(MimicCommLib ${SOURCE_FILES})