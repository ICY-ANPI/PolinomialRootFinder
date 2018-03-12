file(GLOB INCLUDE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.hpp)
add_library (PolynomialRoots ${INCLUDE_SRCS})
add_executable (demo Main.cpp)
target_link_libraries (demo PolynomialRoots)