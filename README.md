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
