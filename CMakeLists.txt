cmake_minimum_required(VERSION 3.5)


project(proyecto01 VERSION 0.0.0 LANGUAGES CXX)


add_subdirectory (src)
add_subdirectory (test)
enable_testing ()
add_test(NAME MyTest COMMAND Test)

#add_subdirectory(benchmark)

