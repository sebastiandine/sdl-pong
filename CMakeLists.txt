cmake_minimum_required(VERSION 3.10)
project(SDL-Pong CXX)

# (Optional) Specify your C++ standard
set(CMAKE_CXX_STANDARD 11)

# ---[ SDL BUILD OPTIONS ]------------------------------------------------
#option(SDL_TEST "" OFF)          # Do not build SDL test programs
option(SDL2TTF_VENDORED "" ON)        # use vendored copies of dependencies instead of relying on the build system
option(SDL2MIXER_VENDORED "" ON)        # use vendored copies of dependencies instead of relying on the build system

# ---[ Add include directories with header files ] ----------
include_directories(
    src/objects
    src/scenes
)

# ---[ Add dependency subdirectories to build them ]-------------------------------------------
add_subdirectory(external/SDL)
add_subdirectory(external/SDL_ttf)
add_subdirectory(external/SDL_mixer)

# ---[ Build executable from sources ]--------------------------------------------------
# Source files
file(GLOB SOURCES
    src/objects/*.cpp
    src/scenes/*.cpp
    main.cpp
)
if(WIN32)
    add_executable(sdl_pong WIN32 ${SOURCES}) # On Windows, specify WIN32 to prevent console window if desired
else()
    add_executable(sdl_pong ${SOURCES})
endif()


# ---[ Link executable and dependencies ]--------------------------------------------------
if(BUILD_SHARED_LIBS)
    target_link_libraries(
        sdl_pong
        PRIVATE
            SDL2::SDL2
            SDL2_ttf::SDL2_ttf
            SDL2_mixer::SDL2_mixer
    )
else()
    target_link_libraries(
        sdl_pong
        PRIVATE
            SDL2::SDL2-static
            SDL2_ttf::SDL2_ttf-static
            SDL2_mixer::SDL2_mixer-static
    )
endif() 
