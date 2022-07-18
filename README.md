# tetris

tetris game writed with c++ and SDL2

## resource.h creation
```
rm -f resources.h
cd resources
for file in `ls`; do
echo "Converting file" $file
xxd -i $file >> resources.h
done
```

## build for windows
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cd build
msbuild tetris.sln /property:Configuration=Release
cp _deps\sdl2-build\Release\SDL2.dll Release
cp _deps\sdl2_image-build\Release\SDL2_image.dll Release
cp _deps\sdl2_mixer-build\Release\SDL2_mixer.dll Release
```

## run 
```
cd build\Release
.\tetris.exe
```

## controls
- `space` for start
- `left/right arrows` for move to sides
- `down arrow` for drop
- `s/up arrow` for rotate clockwise
- `a` for rotate counterclockwise
- `esc` for pause/play game

## demo
[![Demo CountPages alpha](https://j.gifs.com/w0Aoyw.gif)](https://j.gifs.com/w0Aoyw.gif)
