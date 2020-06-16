# CMake generated Testfile for 
# Source directory: /home/mk115227/tests/CommLib/tests
# Build directory: /home/mk115227/tests/CommLib/tests/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(api "/home/mk115227/tests/CommLib/tests/tests/api")
add_test(endpoint "/home/mk115227/tests/CommLib/tests/tests/endpoint")
add_test(mpitransport "/opt/MPI/bin/mpiexec" "-n" "3" "./mpitransport")
subdirs("../googletest-build")
