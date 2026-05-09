# Virtual filesystem

This is a thing used for games, so that you can have easy texture loading / unloading, as well as easy support for community-made packs.

This is mainly used for my minecraft clone where you provide the .jar file and the game uses the assets from there. Added bonus of having easy texturepacks / datapacks

Usage example:

```cpp
vfs fs;

fs.load_zip_or_dir("client-1.21.11.jar");
fs.load_zip_or_dir("texturepack.zip");

auto texture =
    fs.get_file_contents(
        vfs::Path()
        / "assets"
        / "minecraft"
        / "textures"
        / "block"
        / "stone.png"
    ); // can load into something like wgpu-native

auto json =
    fs.get_file_str(
        "assets/minecraft/blockstates/stone.json"
    ); // can load into some json lib
```
