include("${CMAKE_CURRENT_LIST_DIR}/MiMiCCommLibTargets.cmake")

include("@CMAKE_INSTALL_PREFIX@/cmake/MiMiCCommLibTargets.cmake")

set(MiMiCCommLib_INCLUDE_DIRS @CMAKE_INSTALL_PREFIX@/include)
set(MiMiCCommLib_LIBRARIES @CMAKE_INSTALL_PREFIX@/lib/libmimiccomm.a)
set(MiMiCCommLib_Fortran_LIBRARIES @CMAKE_INSTALL_PREFIX@/lib/libmimiccommf.a)