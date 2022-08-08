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

## vnc and http support

- it can be run in container and playable in browser
- tested on ubuntu 20.04.2 LTS
- sounds removed for minimal containerization

# build
``` 
docker build -t tetris:minimal
docker run -d -p 6080:6080 -p 8080:8080 tetris:rest
```
- novnc address : `http://<host|localhost>:6080`
- rest endpoint : `http://<host|localhost>:8080`

### - GET status
````
---> GET http://localhost:8080/tetris/status
<--- 200 text/event-stream

{"board":[
[0,0,0,0,0,1,1,1,1,0],
[0,0,0,0,0,1,1,1,0,0],
[0,0,0,0,0,1,0,0,0,0],
[0,0,0,0,1,1,0,0,1,1],
[1,1,0,0,0,1,1,1,1,0],
[1,1,0,0,0,1,0,1,1,0],
[0,1,0,0,1,1,1,1,0,0],
[0,1,0,1,1,1,1,1,0,0],
[1,1,1,1,1,1,1,1,0,0],
[1,1,1,0,1,1,1,1,1,0],
[1,1,1,1,0,0,1,1,1,1],
[1,1,0,0,1,0,1,1,1,0],
[0,1,0,1,1,1,1,1,1,0],
[1,1,1,1,1,1,1,1,1,0],
[1,1,1,1,1,1,1,1,1,0],
[1,1,1,1,1,1,1,1,1,0],
[1,1,1,1,1,1,1,1,1,0],
[1,1,1,1,1,1,1,1,1,0],
[1,1,1,1,1,1,1,1,1,0],
[1,1,1,1,1,1,1,1,1,0]
],"current":
{"tiles":[
[4,-2],[5,-2],[6,-2],[5,-1]
],
"type":"t"},
"game-over":true,
"level":7,
"next":"s",
"paused":false,
"score":66160,
"started":true,
"statistics":[31,31,34,38,23,27,33]}
````
### - POST command
````
---> POST localhost:8080/tetris/command
---> {"cmd":"left"}
<--- 200
````
### commands
- `"space"` for start
- `"left"/"right"` for move to sides
- `"down"` for drop
- `"s"/"up"` for rotate clockwise
- `"a"` for rotate counterclockwise
- `"esc"` for pause/play game
- `"n"` for new game

### javascript example
````
fetch('http://localhost:8080/tetris/command', {
  method: 'POST',
  body: JSON.stringify({
    cmd: 'left'
  })
})
.then(console.log)

-----------------------------------

var es = new EventSource("http://localhost:8080/tetris/status");
es.onmessage = function(e) {
    console.log(JSON.parse(e.data));
}
````