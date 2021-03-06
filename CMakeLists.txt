cmake_minimum_required(VERSION 2.8)
project(game_engine)

# Not sure if this is correct, but fixes c++ x64 arch issues with std
set (CMAKE_CXX_STANDARD 11)
# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package (OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(deps/include)

file(GLOB SOURCE_FILES engine/*.cpp)

add_executable(game_engine ${SOURCE_FILES})
target_link_libraries(game_engine ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES})
target_compile_features(game_engine PRIVATE cxx_range_for)