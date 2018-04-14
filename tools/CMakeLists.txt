project(TOOLS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
 
add_subdirectory(terrainGenerator)
add_subdirectory(dataGenerator)
add_subdirectory(animGenerator)
add_subdirectory(PathMapFromTiled)
