cmake_minimum_required(VERSION 3.3)
project(MimicCommLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

set(SOURCE_FILES message/Message.h transport/Transport.h MessageApi.h serializer/Serializer.h message/FloatArrayData.h message/SystemData.h message/BaseMessageData.h transport/MPITransport.cpp transport/MPITransport.h transport/Endpoint.h transport/Server.cpp transport/Server.h transport/Client.cpp transport/Client.h message/ClientData.h DataTypes.h)
add_library(mimiccomm STATIC ${SOURCE_FILES})