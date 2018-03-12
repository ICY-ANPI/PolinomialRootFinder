find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${CMAKE_SOURCE_DIR}/include
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.hpp)
add_executable (Test ${TEST_SRCS})
target_link_libraries (Test
                       PolynomialRoots
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )