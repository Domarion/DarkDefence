project(GlobalScriptsTests)
add_executable (TileMapManagerTests TileMapManagerTests.cpp)

set(globalScriptsPath ../../src/GlobalScripts)
set(srcPath ../../src)

add_library(tilemap
    ${srcPath}/GraphicsSystem/newSystem/Size.cpp
    ${srcPath}/GraphicsSystem/newSystem/Position.cpp
    ${globalScriptsPath}/TileMapManager.cpp)
target_link_libraries (TileMapManagerTests
                      tilemap
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME MyCompositeTest COMMAND TileMapManagerTests)
