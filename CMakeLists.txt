cmake_minimum_required(VERSION 3.10)
project(SDL-Pong CXX)

# (Optional) Specify your C++ standard
set(CMAKE_CXX_STANDARD 11)

option(BUILD_SHARED_LIBS "" OFF)        # Disable building SDL as a shared library
# ---[ SDL BUILD OPTIONS ]------------------------------------------------
# option(SDL_SHARED "" OFF)        # Disable building SDL as a shared library
# option(SDL_STATIC "" ON)         # Enable building SDL as a static library
option(SDL_TEST "" OFF)          # Do not build SDL test programs

# ---[ SDL_TTF BUILD OPTIONS ]------------------------------------------------
option(SDL2TTF_VENDORED "" ON)        # use vendored copies of dependencies instead of relying on the build system
option(SDL2MIXER_VENDORED "" ON)        # use vendored copies of dependencies instead of relying on the build system

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

if(WIN32 AND MSVC)
    # when the compiler on Windows is the Microsoft Compiler (Visual Studio), we need to configure this linker flag so 
    # the main function is recognized properly. 
    set_target_properties(sdl_pong PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()


# If you prefer shared versions, just replace the “-static” targets
# with “SDL3::SDL3”, “SDL3_ttf::SDL3_ttf”, etc.
#
target_link_libraries(
    sdl_pong
    PRIVATE
        SDL2::SDL2-static
        SDL2_ttf::SDL2_ttf-static
        SDL2_mixer::SDL2_mixer-static
)
