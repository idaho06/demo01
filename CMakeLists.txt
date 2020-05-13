project(demo01)
cmake_minimum_required(VERSION 3.17.2)

# flags

# include files
include_directories( ./src )

# pkg-config calls
find_package(PkgConfig REQUIRED) 

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)

add_subdirectory(src)
file(GLOB_RECURSE Demo01_SOURCES "./src/*.cpp")

add_executable(demo01 ${Demo01_SOURCES})

target_link_libraries(demo01 PUBLIC
    PkgConfig::SDL2
    PkgConfig::SDL2_MIXER)
