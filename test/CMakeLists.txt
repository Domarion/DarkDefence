find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
#add_executable (Test test.cpp)
#target_link_libraries (Test
#                       Sqr
#                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
#                       )
#add_test (NAME MyTest COMMAND Test)
