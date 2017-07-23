project(AnimSaver)

set(RenderingSystem_INCLUDE_DIRS ../../src)


set(HEADERS
    ${RenderingSystem_INCLUDE_DIRS}/SDL_Engine.h
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Font.h
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/UtilityStructs.h

    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Texture2D.h
    ${RenderingSystem_INCLUDE_DIRS}/Logging/Logger.h

    ${RenderingSystem_INCLUDE_DIRS}/Utility/textfilefunctions.h
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/RenderingSystem.h
    src/AnimSaver.hpp
    )

set(SRC_LIST
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Size.cpp
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Position.cpp
    ${RenderingSystem_INCLUDE_DIRS}/SDL_Engine.cpp

    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Font.cpp

    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/Texture2D.cpp
    ${RenderingSystem_INCLUDE_DIRS}/Logging/Logger.cpp

    ${RenderingSystem_INCLUDE_DIRS}/Utility/textfilefunctions.cpp
    ${RenderingSystem_INCLUDE_DIRS}/GraphicsSystem/newSystem/RenderingSystem.cpp
    src/AnimSaver.cpp
    src/main.cpp
    )


include_directories(${RenderingSystem_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(AnimSaver ${HEADERS} ${SRC_LIST})
target_link_libraries( AnimSaver ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
