# renderer

A raycasting renderer inspired by _Wolfenstein 3D_

## dependencies

- [SDL3](https://wiki.libsdl.org/SDL3/FrontPage)
- [SDL_ttf](https://wiki.libsdl.org/SDL3_ttf/FrontPage)
- [SDL_image](https://wiki.libsdl.org/SDL3_image/FrontPage)

## usage

```bash
cd renderer
cmake -S . -B build
cmake --build build
cd build
./renderer
```

## controls

- Q, E - Strafe left/right
- W, S - Move forward/back
- A, D - Rotate left/right

![raycast demo](assets/img/demo.png)

## acknowledgements

Font: [Home Video Font](https://ggbot.itch.io/home-video-font)
Texture: [Quake-like Sci-fi 64x64](https://level-eleven-games.itch.io/quake-like-texture-pack)
