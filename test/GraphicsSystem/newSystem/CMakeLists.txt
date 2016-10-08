project(newSystemTests)

add_executable (CompositeTest CompositeTest.cpp)
set(newSystemPath ../../../src/GraphicsSystem/newSystem)
set(srcPath ../../../src)

add_library(composite ${newSystemPath}/Composite.cpp
    ${newSystemPath}/Leaf.cpp
    ${newSystemPath}/UtilityStructs.cpp
    ${srcPath}/Input/InputHandler.cpp
    )
target_link_libraries (CompositeTest
                      composite
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME MyCompositeTest COMMAND CompositeTest)



add_executable (RendererTest RenderingSystemTest.cpp)
add_library(RenderingSystem ${newSystemPath}/RenderingSystem.cpp ${newSystemPath}/UtilityStructs.cpp)

target_link_libraries (RendererTest
    RenderingSystem
    ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test (NAME MyRendererTest COMMAND RendererTest)
