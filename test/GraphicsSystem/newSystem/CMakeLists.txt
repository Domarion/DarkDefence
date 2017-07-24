project(newSystemTests)

set(newSystemPath ../../../src/GraphicsSystem/newSystem)
set(srcPath ../../../src)

add_executable (CompositeTest CompositeTest.cpp)


add_library(composite
    ${srcPath}/Logging/Logger.cpp
    ${newSystemPath}/Size.cpp
    ${newSystemPath}/Position.cpp
    ${newSystemPath}/Composite.cpp
    ${newSystemPath}/Leaf.cpp
    ${srcPath}/Input/InputHandler.cpp)

target_link_libraries (CompositeTest
                      composite
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME MyCompositeTest COMMAND CompositeTest)

add_executable (RendererTest RenderingSystemTest.cpp)
add_library(
    RenderingSystem
    ${newSystemPath}/RenderingSystem.cpp
    ${srcPath}/Logging/Logger.cpp

    ${newSystemPath}/Size.cpp
    ${newSystemPath}/Position.cpp)

target_link_libraries (RendererTest
    RenderingSystem

    ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test (NAME MyRendererTest COMMAND RendererTest)


add_executable (UIScrollListTest UIScrollListTest.cpp)
add_library(UIScrollList
    ${srcPath}/Logging/Logger.cpp
    ${newSystemPath}/Size.cpp
    ${newSystemPath}/Position.cpp
    ${newSystemPath}/ConcreteUIViews/UIScrollList.cpp
    ${newSystemPath}/UIElement/ConcreteComposite.cpp
    ${newSystemPath}/Composite.cpp
    ${srcPath}/Input/InputHandler.cpp)

target_link_libraries (UIScrollListTest
    UIScrollList
    ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test (NAME MyUIScrollListTest COMMAND UIScrollListTest)
