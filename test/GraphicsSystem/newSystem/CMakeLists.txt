project(newSystemTests)

add_executable (CompositeTest CompositeTest.cpp)
set(newSystemPath ../../../src/GraphicsSystem/newSystem)
add_library(composite ${newSystemPath}/Composite.cpp ${newSystemPath}/Leaf.cpp ${newSystemPath}/UtilityStructs.cpp)
target_link_libraries (CompositeTest
                      composite
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME MyCompositeTest COMMAND CompositeTest)

add_executable (RendererTest RenderingSystemTest.cpp)
target_link_libraries (RendererTest
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test (NAME MyRendererTest COMMAND RendererTest)
