project(PathMapGenerator)

set(RenderingSystem_INCLUDE_DIRS ../../src)
set (CerealInclude ../../external/cereal/include)

set(HEADERS
    src/PathMapGenerator.hpp
    )

set(SRC_LIST
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Size.cpp
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Position.cpp

    src/PathMapGenerator.cpp
    src/main.cpp
    )


include_directories(${RenderingSystem_INCLUDE_DIRS} ${CerealInclude})

add_executable(PathMapGenerator ${HEADERS} ${SRC_LIST})
