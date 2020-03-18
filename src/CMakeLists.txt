set(SOURCE_FILES message/Message.h transport/Transport.h MCLf2c.h MCLf2c.cpp MessageApi.h MessageApi.cpp MCLMain.h serializer/Serializer.h message/FloatArrayData.h message/SystemData.h message/BaseMessageData.h transport/MPITransport.cpp transport/MPITransport.h transport/Endpoint.h transport/Server.cpp transport/Server.h transport/Client.cpp transport/Client.h message/ClientData.h DataTypes.h transport/MPMDTransport.cpp transport/MPMDTransport.hpp)
set(HEADER_FILES MessageApi.h DataTypes.h MCLMain.h MCLf2c.h)

if(BUILD_FORTRAN_API)
    set(CMAKE_Fortran_MODULE_DIRECTORY ${PROJECT_BINARY_DIR}/include)
    list(APPEND mclfortran.mod)
    add_library(mclfortran STATIC MCLfortran.f90)
    install(TARGETS mclfortran DESTINATION include)
endif()
if (BUILD_SHARED)
    add_library(mimiccomm SHARED ${SOURCE_FILES})
else()
    add_library(mimiccomm STATIC ${SOURCE_FILES})
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
