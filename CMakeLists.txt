cmake_minimum_required(VERSION 3.22)
project(SpaceHunter)

set(CMAKE_CXX_STANDARD 17)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME} scripts/main.cpp
        scripts/Utilities/Character.cpp
        scripts/Utilities/Character.hpp
        scripts/Player/Player.cpp
        scripts/Player/Player.hpp
        scripts/Background/Background.cpp
        scripts/Background/Background.hpp
        scripts/Player/Bullet.cpp
        scripts/Player/Bullet.hpp
        scripts/Menu/Menu.cpp
        scripts/Menu/Menu.hpp
        scripts/Menu/Menu.cpp
        scripts/Menu/Menu.hpp
        scripts/Utilities/SDL_Wrapper.cpp
        scripts/Utilities/SDL_Wrapper.hpp)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2_image REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})