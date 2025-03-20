# SDL Pong
This is a simple implementation of the classic Pong game using C++ and SDL2.

![](img.png)

## Dependencies 
Dependencies of this project are management as git submodules.

| Dependency | Version | Application |
| --- | --- | --- |
| [SDL](https://github.com/libsdl-org/SDL) | [2.32.2 (e11183e)](https://github.com/libsdl-org/SDL/commit/e11183ea6caa3ae4895f4bc54cad2bbb0e365417) | general application structure, especially rendering, orchestration and input handling |
| [SDL_ttf](https://github.com/libsdl-org/SDL_ttf) | [2.24.0 (2a89147)](https://github.com/libsdl-org/SDL_ttf/commit/2a891473eaf05ba1707a4b7913e6c4db7de7458a) | rending TrueType fonts in SDL applcations | 
| [SDL_mixer](https://github.com/libsdl-org/SDL_mixer) | [2.8.1 (171eb2d)](https://github.com/libsdl-org/SDL_mixer/commit/171eb2d420d5643e4ee11514a06e04a41a463bbd) | audio mixer for SDL applcations |

## How To Build 
**Note:** To build the project, your build systems needs to provide a **C++ 11** compiler and **CMake 3.x**.

First, clone the project and fetch the dependencies as git submodules recursively:
```
$ git clone <this_project_url>
$ cd <local_project_dir>
$ git submodule update --init --recursive
```

Additional notes on building the project:
* The provided `CMakeLists.txt` respects the `BUILD_SHARED_LIBS` build option to either the build the project statically or dynamically linked (default is dynamically linked).
* All build artifacts are placed into the `build/` directory. To have a fully functional buildy, you need to also copy the `assets/` directory into `build/` for the binary to resolve references to assets properly. Also, if you chose dynamic linking, you need to copy the dynamic libaries (`.dll` or `.so`) of the dependencies to the same directory level as the applcation binary. You can refer to the [GitHub pipeline bundling sections](.github/workflows/cmake-multi-platform.yml) on how to bundle a fully functional build properly. 

### Building on Linux
Dynamic Linking
```
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

Static Linking
```
$ cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
$ cmake --build build
```

### Building on Windows

Dynamic Linking (MSVC compiler)
```
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

Static Linking (MSVC compiler )
```
$ cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
$ cmake --build build
```

Dynamic Linking (MinGW compiler)
```
$ cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

Static Linking (MinGW compiler)
```
$ cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
$ cmake --build build
```

## Containerized Dev Environment 
This project provides configuration for a [VSCode development container](https://code.visualstudio.com/docs/remote/containers) at `.devcontainer/`. Via this configuration, you automatically have a complete (Debian-based) development environment for the project. 
Additionally, to run the UI out of the container, you need to use a X11 server. I will briefly explain how to run them in order to display the GUI from the container:

**Windows**<br>
You need to install an X-server like [VcXSrv](https://sourceforge.net/projects/vcxsrv/) or [Xming](https://sourceforge.net/projects/xming/). Once you have it installed, start it via `xlaunch.exe` and enable the option `Disable access control` before you start the development container. Now, you can start a GUI app in your container that will be displayed via the X-server on the host system.

For running audio from your development container, you need a [PulseAudio](https://www.freedesktop.org/wiki/Software/PulseAudio/) server on the host to forward sound from a Docker container to the host.

1. Download the PulseAudio server for Windows
   https://www.freedesktop.org/wiki/Software/PulseAudio/Ports/Windows/Support/

2. Unzip the download and make the following adjustment in the config file at `pulseaudio-1.1/etc/pulse/default.pa`:
   In section `### Network access`, uncomment the line `load-module module-native-protocol-tcp`, and extend it as follows:
   
    ```
    load-module module-native-protocol-tcp listen=0.0.0.0 auth-anonymous=1
    ```

   This configures the PulseAudio server to accept any incoming client.

3. Start the PulseAudio server by executing `pulseaudio-1.1/bin/pulseaudio.exe`
   Easiest way is to execute it from command line and displaying the pid file.
    ```
    pulseaudio-1.1/bin/pulseaudio.exe --use-pid-file=false
    ```