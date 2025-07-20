# BSP-Entity-Manager
This repository has a fully open source of BSP Entity Manager for GoldSrc games.

![CMake Presets](https://img.shields.io/badge/CMake-Presets-informational?style=plastic) ![Compiler](https://img.shields.io/badge/compiler-GCC-yellow?style=plastic)
![Language](https://img.shields.io/badge/language-c++20-e76089?style=plastic) ![](https://img.shields.io/badge/arch-x64%20%7C%20x86-d9654f?style=plastic) ![](https://img.shields.io/badge/config-Debug%20%7C%20Release-c0c0c0?style=plastic) ![](https://img.shields.io/badge/license-GNU-green?style=plastic)


## How to build BSP Entity Manager?
* You don't need to build project if you will just use you can find both x86 / x64 architecture of app by downloading [BSP-Entity-Manager.zip](https://github.com/kruz1337/BSP-Entity-Manager/releases)

* Firstly, you can download project files directly or you can clone it by using git.

* If you are using Windows, install [MSYS2](https://www.msys2.org/) and make sure you install `Ninja Compiler`, `GNU Compiler Collection` packages in Mingw64 or Ucrt64 environments (you can install x86 packages if you want to build for x86). 

* Before compiling it you need to modify paths in `CMakePresets.json` because i used ucrt64 environment for building x64. 

* Make sure you have installed [CMake](https://cmake.org/download/) on your device.

* There is 4 presets, you can compile whichever you want by using CMake terminal commands or using CMake GUI app.

* Binary files will be compiled in bin folder

## How to use arguments?
* BSP_Entity_Manager.exe `"BSP File Path" [--config "Config Path" | --entity "Entity File Path"] [--export "Export Path" | --save "Save Path"]`
  
* You can use one from each of the two brackets group.
  
* `--config`: Changes values by searching keys. Its not supports comments dont add any comment on config file use only `"key" = "value"` or `key = value` format for every single line and.

* `--entity`: Directly imports entity file which you exported before.

* `--export`: It will export entity file. Typing path is not required. 

* `--save`: It will save bsp file, if you wont enter file path it will overwrite.
