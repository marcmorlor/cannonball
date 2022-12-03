# CMake setup used for SDL2/GLES builds on Raspberry Pi

set(CMAKE_CXX_FLAGS "-I/opt/vc/include -L/opt/vc/lib")

set(lib_base /usr/include)
set(sdl_root ${lib_base}/SDL2)

include_directories(
    "${sdl_root}"
    "/usr/local/include"
)

link_libraries(cannonball 
    SDL2
    brcmGLESv2
    wiringPi
)

# Linking
link_directories(
    "${sdl_root}/lib"
    "/usr/local/lib"
)

add_definitions(-O3 -DSDL2 -DWITH_OPENGLES -mcpu=arm1176jzf-s -mfloat-abi=hard -mfpu=vfp -lwiringPi)
#add_definitions(-O0 -ggdb -DSDL2 -DWITH_OPENGLES -lwiringPi)
 
# Location for Cannonball to create save files
# Used to auto-generate setup.hpp with various file paths
set(xml_directory ./)
set(sdl_flags "SDL_WINDOW_RESIZABLE")

# Set SDL2 instead of SDL1
set(SDL2 1)
