cmake_minimum_required(VERSION 3.5)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()


project(proyecto01 VERSION 0.0.0 LANGUAGES CXX)


add_subdirectory (src)
add_subdirectory (test)
enable_testing ()
add_test(NAME MyTest COMMAND Test)

#add_subdirectory(benchmark)

