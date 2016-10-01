project(TESTS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${SDL2_INCLUDE_DIRS}

                     ../${TESTS}/
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test GraphicsSystem/newSystem/CompositeTest.cpp)
add_library(composite ../${TESTS}/src/GraphicsSystem/newSystem/Composite.cpp ../${TESTS}/src/GraphicsSystem/newSystem/Leaf.cpp ../${TESTS}/src/GraphicsSystem/newSystem/UtilityStructs.cpp)
target_link_libraries (Test
                      composite
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME MyTest COMMAND Test)
