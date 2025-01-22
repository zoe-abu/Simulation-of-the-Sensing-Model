# Simulation-of-the-Sensing-Model


# OpenGL环境配置windows版.md
# 编译工具
## 安装gcc （MinGW）
* 下载：
[https://github.com/niXman/mingw-builds-binaries/releases](https://github.com/niXman/mingw-builds-binaries/releases)
* 解压到c盘根目录
* 配置bin到环境变量Path


下载好的mingw：[mingw64](x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev0.7z)

![image](images/q0sVPBnHVW1qPI1GL43yVzbgYFAN8xGb0SrJYelnzf4.png)

![image](images/1GhGaRnvJn1SFaXnwzIRpDHlfQYI0l_jRZ079cdPDCM.png)



## CMake
下载：

[https://cmake.org/download/](https://cmake.org/download/)

下载好的cmake:[cmake](cmake-3.31.0-rc3-windows-x86_64.msi)
配置path环境变量：

> C:\\Program Files\\CMake\\bin  （如上图所示）

reference：

[https://blog.csdn.net/FatalFlower/article/details/108686549](https://blog.csdn.net/FatalFlower/article/details/108686549)



## vscode
下载vscode：

[https://code.visualstudio.com/](https://code.visualstudio.com/)

配置gcc和cmake：

[https://blog.csdn.net/m0\_50866704/article/details/137509106](https://blog.csdn.net/m0_50866704/article/details/137509106)

![image](images/neoZMUUXUgVC-vsXwiKgh_-345qlPeVMWFWQ01_Bk5g.png)

![image](images/dPwMBTSFr4a5EEizoY2cNrMUpxU2xMP7Ny9-T1csoR8.png)

* 还是要自己写CMakeLists.txt
* 工具行状态栏可以配置`cmake release/debug`、`编译工具选择gcc`、`生成`、`运行`，鼠标悬停既有提示，可挨个看下
* `修改保存CMakeLists.txt后`，cmake插件自动cmake到build文件夹下，生成makefile，但并不会执行编译，mingw32-make

* 点击下方状态栏上的`螺母图标`，能够直接cmake生成makefile，并使用编译工具编译生成exe
* 点击`运行图标`可以生成并运行程序



# 第三方库
## glut
下载：

[https://sourceforge.net/projects/freeglut/](https://sourceforge.net/projects/freeglut/)

编译：

```bash
生成makefiles：
cmake -G "MinGW Makefiles" -S . -B .

编译：
cmake --build .
```
> \-S后面是源代码根目录，-B后面是build目录，根据自己的情况配置



## glew
下载：

[http://glew.sourceforge.net/index.html](http://glew.sourceforge.net/index.html)

编译：

```bash
进入目录：
cd build/cmake

生成makefiles：
cmake -G "MinGW Makefiles" -S . -B .

编译：
mingw32-make
或
cmake --build .
```


## glfw
[https://www.glfw.org/](https://www.glfw.org/)

2）使用GUI cmake生成makefile：

通过GUI界面：

![image](images/EQ8sKqKltaJROWe79I7jRzztyYBwjmRUCtlmI0b332s.png)

或者通过命令行（更简洁）：

```bash
cmake -G "MinGW Makefiles" -S . -B .
```
> GUI里面也只是配置了代码树路径、build路径、编译工具类型。只是一些cmake选项能够可视化勾选，在命令行里面赋值也是一样的。

相关文件参照（目录可能不一致）：

![image](images/_C3pWwVqRkIciAdsJWq7mCcTvaOPeg3E5bEEKjlIHKY.png)

![image](images/3pP5RIyeWPZw4nQHlOr1bQKrioObAqLVQtma7Kc14Eg.png)

3）编译glfw

生成Makefiles后，进入编译目录进行编译

```bash
进入目录：
cd build

进行编译：
cmake  --build .
or:
mingw32-make
```
![image](images/VwxcZZ7bYxKY3AEyMXRDLaEcAyekGBfnXPvG7xuZGzw.png)

![image](images/ECix737lLtu4TVyDTYyEYyk2yV23EYV-xsWkRoKwS7c.png)

![image](images/XxKkfRBya0tPa7xpuECQg4eA2GSlNcL-SqRC8SHkr14.png)




## glad
下载源码：

[https://glad.dav1d.de/](https://glad.dav1d.de/)

选项参考

![image](images/NN60vV4h5YPWw6TNmlYkiVzN6g20L3ORvrtKUI-DA-c.png)

编译：

```bash
gcc ./src/glad.c -c -Iinclude
ar -rc libglad.a glad.o
```
![image](images/4PDSN4C_YkBQFTAFGMVLW108hv_mOeYLsZTAlYlLoLE.png)



## soil 
下载：

[http://www.lonesock.net/files/soil.zip](http://www.lonesock.net/files/soil.zip)

编译：

```bash
进入项目根目录，然后：
mkdir build
cd build 
cmake .. -G "MinGW Makefiles"
cmake --build .
```


reference：[https://blog.csdn.net/chy19911123/article/details/46642075](https://blog.csdn.net/chy19911123/article/details/46642075)

## glm
下载：

[https://github.com/g-truc/glm](https://github.com/g-truc/glm)

编译：

官方文档如下（可以参照上面编译其他库的指令）

```Plain Text
cd /path/to/glm

cmake \
    -DGLM_BUILD_TESTS=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -B build .

cmake --build build -- all
cmake --build build -- install
```
> Passing `-DBUILD_SHARED_LIBS=ON` to build shared library


# OpenGL教程
着色器：[https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/05%20Shaders/](https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/05%20Shaders/)

纹理：[https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/06%20Textures/](https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/06%20Textures/)

相机视角：[https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/09%20Camera/](https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/09%20Camera/)

光照模型：[https://learnopengl-cn.readthedocs.io/zh/latest/02%20Lighting/06%20Multiple%20lights/](https://learnopengl-cn.readthedocs.io/zh/latest/02%20Lighting/06%20Multiple%20lights/)



# Demo
代码：[multilight-demo1.zip](multilight-demo1.zip)

手动编译：

CMakeLists.txt配置项目

```makefile
cmake_minimum_required(VERSION 3.0.0)
project(multi-light)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")
message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
set(SOURCE_FILES src/main.cpp) # set(SOURCE_FILES src/main.cpp src/glad.c)
add_executable(main ${SOURCE_FILES})
target_link_libraries(main soil glfw3 glad glew32 freeglut_static opengl32 glm) 
```
注意In Windows:

* OpenGL  library is called `opengl32` not `GL` 
* make is called `mingw32-make` not `make`

Shell指令：

```bash
cd build 

cmake .. -G "MinGW Makefiles"  

mingw32-make    （文件夹路径中不能有中文）
或
cmake --build .
```
建议vscode中借助cmake插件自动编译并运行：

* 点击左下角第一个三角形配置、编译并运行
* 左侧的目录结构中可以看到上面编译的静态库和头文件
* 配置CMakeLists.txt 申明要编译的代码文件、头文件目录、库文件目录、要链接的库文件

![image](images/xInCkJTpY2KvoAENpqtbk4dYwCWY17SBT71LnkLAkBQ.png)

运行界面：

![image](images/MxxzVcYfOSG2EjZmQjipSBpoH8hBpUK2vzaIOmf9BGE.png)

* 通过鼠标可以改变观察视角
* 按ESC退出



# Reference
* [https://blog.csdn.net/FatalFlower/article/details/108686549](https://blog.csdn.net/FatalFlower/article/details/108686549)
* [https://blog.csdn.net/qq\_36286899/article/details/119654550](https://blog.csdn.net/qq_36286899/article/details/119654550)
* [https://blog.csdn.net/Fyantu/article/details/123420415](https://blog.csdn.net/Fyantu/article/details/123420415)
* [https://www.khronos.org/opengl/wiki/Getting\_Started](https://www.khronos.org/opengl/wiki/Getting_Started)
* [https://zhuanlan.zhihu.com/p/438768458](https://zhuanlan.zhihu.com/p/438768458)
* [https://zhuanlan.zhihu.com/p/4260260851](https://zhuanlan.zhihu.com/p/4260260851)
* [https://stackoverflow.com/questions/24847847/glviewport-undefined-reference](https://stackoverflow.com/questions/24847847/glviewport-undefined-reference)

Hello experienced programmers. Your humble questioner returns. Today me and my friend decided to start/learn OpenGL. As we follow [this](http://www.learnopengl.com/) tutorial, we have stuck at `glViewport` as it gives `Undefined reference` error. We are working on NetBeans 8.0 C/C++ version. I have double checked the `Makefile` as some sites mentioned `-Lpath -lglew32 -lglfw3` had to be last parameter when compiling. I have tried to ad `-lGL` as linker option, but sadly it won't work.

In Windows the OpenGL API interface library is called `opengl32` not `GL`, hence you must link with

```Plain Text
-lopengl32
```
(note that it's always …32, even on 64 bit systems).
