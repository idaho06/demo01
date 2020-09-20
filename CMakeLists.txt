cmake_policy(SET CMP0048 NEW) # For using VERSION in "project"
project(demo01 VERSION 1.0 DESCRIPTION "XMas demo 2020")
cmake_minimum_required(VERSION 3.16.3)

# include files
include_directories( 
    "./src" 
    )

# pkg-config calls
find_package(PkgConfig REQUIRED) 

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)

#add_subdirectory(src)

add_executable(demo01
    src/main.cpp
    src/sdlmanager.cpp
    src/texturemanager.cpp
    src/surface.cpp
    src/effect.cpp
    src/fastsin.cpp
    src/hdispl.cpp
    src/rippledispl.cpp
    src/fire.cpp
    )

target_link_libraries(demo01 PUBLIC
    PkgConfig::SDL2
    PkgConfig::SDL2_MIXER)

# compile options
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
