project(DarkDefence)
cmake_minimum_required(VERSION 2.8)
add_subdirectory(src)
enable_testing ()
add_subdirectory(test)
add_subdirectory(tools)

file(COPY GameData DESTINATION ${CMAKE_BINARY_DIR}/src)
file(COPY Fonts DESTINATION ${CMAKE_BINARY_DIR}/src)
