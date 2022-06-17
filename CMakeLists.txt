cmake_minimum_required(VERSION 3.21)
project(tetris)

### create resource header ###
#[[
header=resources.h
cd resources
for file in `ls`; do
echo "Converting file" $file
xxd -i $file >> header
done
]]

### windows build ###
#[[
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cd build
msbuild tetris.sln /property:Configuration=Release
cp _deps\sdl2-build\Release\SDL2.dll Release
cp _deps\sdl2_image-build\Release\SDL2_image.dll Release
cp _deps\sdl2_mixer-build\Release\SDL2_mixer.dll Release
]]

### run ###
#[[
cd build\Release
.\tetris.exe
]]

include(FetchContent)

# sdl2
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY  https://github.com/libsdl-org/SDL
        GIT_TAG         a5949d7b035feb74228882c47ea37b9b29fbb87c
        GIT_PROGRESS    TRUE
)

# sdl2_image
FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image
        GIT_TAG 3438bb17c0e17d5bed7df7f03dc3ffefc886db1e
        GIT_PROGRESS    TRUE
)

# sdl2_mixer
FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY  https://github.com/libsdl-org/SDL_mixer
        GIT_TAG ab8301a2c7e201d833808ca9ac132aac8150f870
        GIT_PROGRESS    TRUE
)
FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer)

set(SDL2_LIBRARIES ${SDL2_LIBRARIES} SDL2 SDL2main SDL2_image SDL2_mixer)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VERBOSE_MAKEFILE ON)
add_executable(tetris WIN32 main.cpp blocks.cpp window.cpp game.cpp media_sdl2.cpp media_sdl2_release.cpp)
target_link_libraries(tetris ${SDL2_LIBRARIES})