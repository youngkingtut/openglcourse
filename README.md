### Purpose
Going through a series of lectures to re-enlighten my understanding of OpenGL.

Lectures are found [here](https://www.udemy.com/course/graphics-with-modern-opengl/).

### Setup

#### Setup submodules
```shell
git submodule init
git submodule update
```

#### Build glew
Mac/Linux can simply run make in ext/glew/auto
```shell
cd ext/glew/auto
make
```

Windows requires downloading the source [here](http://glew.sourceforge.net/) and replacing ext/glew with the unzipped
download.


### Issues with Assimp
Ran into a few issues attempting to build Asset importer on windows with MinGW32
- Werror compiler flag kills it all together [lots of warnings!!].
 - comment out line assimp/code/CMakeLists.txt:1142: TARGET_COMPILE_OPTIONS(assimp PRIVATE -Werror)
- ssize_t typedef is defined in multiple places
 - change ssize_t to sssize_t in contrib/zip/src/zip.*
- error: cannot convert 'CRITICAL_SECTION*
 - https://github.com/assimp/assimp/issues/1750
