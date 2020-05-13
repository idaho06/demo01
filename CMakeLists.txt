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

add_executable(demo01 ./src/main.cpp )

target_link_libraries(demo01 PUBLIC
    PkgConfig::SDL2
    PkgConfig::SDL2_MIXER)
