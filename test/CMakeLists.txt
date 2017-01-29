project(TESTS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${SDL2_INCLUDE_DIRS}

                     ../${TESTS}/
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)

add_subdirectory(GraphicsSystem/newSystem)
add_subdirectory(GlobalScripts)
