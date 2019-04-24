# CMake generated Testfile for 
# Source directory: /home/lordalveric/development/cpp_proj/merseburg-incantation/tests
# Build directory: /home/lordalveric/development/cpp_proj/merseburg-incantation/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(simple_test "/home/lordalveric/development/cpp_proj/merseburg-incantation/tests/simple_test.cpp" "PUBLIC" "MERSEBERG")
subdirs("gmock")
