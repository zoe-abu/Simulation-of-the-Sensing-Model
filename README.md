# Simulation-of-the-Sensing-Model


## Install gcc （MinGW）
* Download：[https://github.com/niXman/mingw-builds-binaries/releases](https://github.com/niXman/mingw-builds-binaries/releases)
* Add bin to Path

## Install CMake
* Download: [https://cmake.org/download/](https://cmake.org/download/)
* Configure the Path environment variable: C:\\Program Files\\CMake\\bin

reference：[https://blog.csdn.net/FatalFlower/article/details/108686549](https://blog.csdn.net/FatalFlower/article/details/108686549)


# Third-party Libraries
## glut
* Download：[https://sourceforge.net/projects/freeglut/](https://sourceforge.net/projects/freeglut/)
## glew
* Download：[http://glew.sourceforge.net/index.html](http://glew.sourceforge.net/index.html)
## glfw
* Download：[https://www.glfw.org/](https://www.glfw.org/)
## glad
* Download：[https://glad.dav1d.de/](https://glad.dav1d.de/)
## soil 
* Download：[http://www.lonesock.net/files/soil.zip](http://www.lonesock.net/files/soil.zip)
## glm
* Download：[https://github.com/g-truc/glm](https://github.com/g-truc/glm)
  
## Compile for the third libraries：
```bash
 Generate makefiles：cmake -G "MinGW Makefiles" -S . -B .
 compile：cmake --build .
```
The -S option refers to the root directory of the source code, and the -B option specifies the build directory. Adjust these according to your setup.


Note for Windows:

* OpenGL  library is called `opengl32` not `GL` 
* make is called `mingw32-make` not `make`

## Shell commands for compiling this project：

```bash
cd build 

cmake .. -G "MinGW Makefiles"  

mingw32-make    (Note: No Chinese characters in the folder path)
or
cmake --build .
```

## Reference
* [https://blog.csdn.net/FatalFlower/article/details/108686549](https://blog.csdn.net/FatalFlower/article/details/108686549)
* [https://blog.csdn.net/qq\_36286899/article/details/119654550](https://blog.csdn.net/qq_36286899/article/details/119654550)
* [https://blog.csdn.net/Fyantu/article/details/123420415](https://blog.csdn.net/Fyantu/article/details/123420415)
* [https://www.khronos.org/opengl/wiki/Getting\_Started](https://www.khronos.org/opengl/wiki/Getting_Started)
* [https://zhuanlan.zhihu.com/p/438768458](https://zhuanlan.zhihu.com/p/438768458)
* [https://zhuanlan.zhihu.com/p/4260260851](https://zhuanlan.zhihu.com/p/4260260851)
* [https://stackoverflow.com/questions/24847847/glviewport-undefined-reference](https://stackoverflow.com/questions/24847847/glviewport-undefined-reference)


