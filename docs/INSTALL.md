# INSTALLATION GUIDE FOR ZIDE

### Table of contents

* [Get the source code](#get-the-source-code)
* [Compiling](#compiling)
  * [macOS details](#macos-details)

### Get the source code
The zide codebase uses git submodules to manage external dependencies
so, for a fresh clone use the following git command to clone it recursively 
```bash
git clone --recursive https://github.com/bitspaceorg/zide.git
```
and to update an existing clone use the following command
```bash
git pull
git submodule update --init --recursive
```
### Compiling
I believe you know zide uses C++, so you will be needing C++ Complier like clang, gcc, MSVC or MINGW
to compile the source to code to binaries. and we use `CMake` as a build tool, therefore you will also
need cmake installed on you machine.

##### MACOS Details
1. Geting Dependencies
- installing xcode will give you clang compiler by default
- to install cmake, 
    - either go to their official home page and download it [CMake Download](https://cmake.org/download/)
    - **HOMEBREW**
        ```bash
        brew install cmake
        ```
    - **NIX DARWIN** [NIXPKG](https://search.nixos.org/packages?channel=unstable&show=cmake&from=0&size=50&buckets=%7B%22package_attr_set%22%3A%5B%22No%20package%20set%22%5D%2C%22package_license_set%22%3A%5B%5D%2C%22package_maintainers_set%22%3A%5B%5D%2C%22package_platforms%22%3A%5B%5D%7D&sort=relevance&type=packages&query=cmake)
        ```bash
        nix-shell -p cmake
        ```

2. Actual Compiling
first generate CMake Configure files, then build them. You can find the executable in `bin/zide`
```bash
cmake -S . -B build
cmake --build build
./build/bin/zide
```

