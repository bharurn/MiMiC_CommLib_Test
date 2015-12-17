cmake_minimum_required(VERSION 3.3)
project(MimicCommLib)

set(BOOST_ROOT "/home/bolnykh/soft")
set(BOOSTROOT "/home/bolnykh/soft")


find_package(Boost 1.59.0  REQUIRED COMPONENTS
        serialization system)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Lboost_serialization -lgomp")

set(SOURCE_FILES main.cpp message/Message.h transport/SocketTransport.cpp transport/SocketTransport.h transport/Transport.h MessageService.cpp MessageService.h serializer/BoostSerializer.cpp serializer/BoostSerializer.h serializer/Serializer.h message/FloatArrayData.h message/SystemData.h message/BaseMessageData.h transport/BoostSocketTransport.cpp transport/BoostSocketTransport.h)
add_executable(MimicCommLib ${SOURCE_FILES})
target_link_libraries(MimicCommLib ${Boost_LIBRARIES})