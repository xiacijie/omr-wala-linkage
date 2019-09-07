# CMake generated Testfile for 
# Source directory: /Users/cijiexia/Project/lljb/third_party/omr/jitbuilder
# Build directory: /Users/cijiexia/Project/lljb/build_1/third_party/omr/jitbuilder
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestJitBuilderAPIGenerator "/usr/bin/python" "run_tests.py")
set_tests_properties(TestJitBuilderAPIGenerator PROPERTIES  WORKING_DIRECTORY "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/apigen" _BACKTRACE_TRIPLES "/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/CMakeLists.txt;136;add_test;/Users/cijiexia/Project/lljb/third_party/omr/jitbuilder/CMakeLists.txt;0;")
subdirs("release")
