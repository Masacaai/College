if(EXISTS "/home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build/tests[1]_tests.cmake")
  include("/home/masacaai/Code/CS-251/P4-Labyrinth_Escape/build/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
