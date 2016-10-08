project(newSystemTests)
set(newSystemPath ../../../src/GraphicsSystem/newSystem)
set(srcPath ../../../src/)
add_executable (CompositeTest CompositeTest.cpp)

add_library(composite ${newSystemPath}/Composite.cpp ${newSystemPath}/Leaf.cpp ${newSystemPath}/UtilityStructs.cpp)
target_link_libraries (CompositeTest
                      composite
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME MyCompositeTest COMMAND CompositeTest)


add_executable (TileTerrainMakerTest TileTerrainMakerTest.cpp)
add_library(TileTerrainmaker ${newSystemPath}/TileTerrainMaker.cpp
    ${newSystemPath}/Texture2D.cpp
    ${newSystemPath}/Font.cpp
    ${srcPath}/Utility/textfilefunctions.cpp
    ${srcPath}/GlobalScripts/Renderer.cpp
    )

target_link_libraries (TileTerrainMakerTest
    TileTerrainmaker
    ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
add_test (NAME TileTerrainMakerTest COMMAND TileTerrainMakerTest)
#add_executable (RendererTest RenderingSystemTest.cpp)
#target_link_libraries (RendererTest
#    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
#add_test (NAME MyRendererTest COMMAND RendererTest)
