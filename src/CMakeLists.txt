set(SOURCE_FILES
    serializer/Serializer.h
    message/Message.h
    message/FloatArrayData.h
    message/SystemData.h
    message/BaseMessageData.h
    message/ClientData.h
    transport/Transport.h
    transport/MPITransport.cpp
    transport/MPITransport.h
    transport/Endpoint.h
    transport/Server.cpp
    transport/Server.h
    transport/Client.cpp
    transport/Client.h
    transport/MPMDTransport.cpp
    transport/MPMDTransport.hpp
    MCLf2c.h
    MCLf2c.cpp
    MessageApi.h
    MessageApi.cpp
    MCLMain.h
    DataTypes.h
    )
set(HEADER_FILES MessageApi.h DataTypes.h MCLMain.h MCLf2c.h)

add_library(mimiccomm ${SOURCE_FILES})

target_include_directories(mimiccomm PUBLIC ${MPI_C_INCLUDE_DIRS})
target_include_directories(mimiccomm PUBLIC ${MPI_CXX_INCLUDE_DIRS})

if(BUILD_FORTRAN_API)
    set(CMAKE_Fortran_MODULE_DIRECTORY ${PROJECT_BINARY_DIR}/include)
    list(APPEND HEADER_FILES ${CMAKE_Fortran_MODULE_DIRECTORY}/mcl_fortran.mod)
    add_library(mimiccommf fortran/mcl_interface.f90
            fortran/mcl_send_recv.f90
            fortran/mcl_fortran.f90)
    target_include_directories(mimiccommf PUBLIC ${MPI_Fortran_INCLUDE_DIRS})
    install(TARGETS mimiccommf DESTINATION lib EXPORT CommlibTargets)
    set_property(TARGET mimiccommf PROPERTY VERSION ${MimicCommLib_VERSION})
endif()

set_property(TARGET mimiccomm PROPERTY VERSION ${MimicCommLib_VERSION})

install(TARGETS mimiccomm DESTINATION lib EXPORT CommlibTargets)
install(FILES ${HEADER_FILES} DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/MimicCommLibConfigVersion.cmake"
        VERSION ${MimicCommLib_VERSION}
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT CommlibTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/MimicCommLibTargets.cmake"
        NAMESPACE Upstream::
        )

configure_file(${CMAKE_SOURCE_DIR}/cmake/CommlibConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/MimicCommLibConfig.cmake"
        @ONLY
        )

install(EXPORT CommlibTargets
        FILE
        MimicCommLibTargets.cmake
        NAMESPACE
        Upstream::
        DESTINATION
        cmake)

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MimicCommLibConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MimicCommLibConfigVersion.cmake
        DESTINATION
        cmake
        COMPONENT
        Devel)
