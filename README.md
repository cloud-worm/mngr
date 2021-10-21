
<p align="center">
<img src="images/mngr-logo.png" width="208" height="79" style="text-align: center" />
</p>

<p align="center">
<h3 align="center"> A minimal C++ library for system utility, oriented towards simplicity. </h3>
</p>

<br />

`mngr` is a minimal C++ library for various aspects of system management, including, for example, file management. mngr is oriented towards performance and simplicity. 

Instead of explaining the theory, let us observe a practical example to see just how `mngr` works:

```c++
#include "mngr.hpp"

using namespace mngr;

int main()
{
	// Simple mngr "Hello, World!" program
	create_file("Hello.txt");
	add_to_file("Hello.txt", "Hello, World!");
}
```

Just **one simple header file** (everything is self-contained within it) that you have to include, and you have access to a quantity of useful data and methods that frees you of having to use complex tokens such as `oftsream`, `data()`, etc. 

This library was created not only for beginners, who may find some C++ concepts difficult and time-consuming, but also for advanced user/professionals who do not wish to waste their time writing tiresome utility functions.

<br />

### Why use `mngr`, exactly?

`mngr` is different from other C++ libraries because its aim is to be as explicit as possible for the user, in such a way that people who use it do not even need to to look at any documentation when writing: the mere names of the different functions are enough to know what code to write.

This means that `mngr` is heavily based on methods and functions, with little to no templates. Each function serves *one* purpose; for example, you cannot create a directory with the `create_file()` function, and you cannot create a file with the `create_folder()` function.

<br />

### How do you use `mngr`?

`mngr` does not work like a usual C++ library. Instead, you must add `mngr/mngr.hpp` (a self-contained header file) within a project of yours and include it locally.

1. Start by donwloading this repository as .zip, or run 
```bash
git clone "https://github.com/cloud-worm/mngr.git"
```
2. Add the `mngr.hpp` file (located in this repository as `./mngr/mngr.hpp`) somewhere where you can access it easily from your other files. For example, create an `mngr` folder next to your `main.cpp` and place the concerned file there.
3. Remember to **read the license** file before using `mngr`! This project is available under the GNU Public License v3.0.
4. Include the file locally. For example, within your `main.cpp`, you can use:
```c++
#include "./mngr/mngr.hpp"
```
5. `mngr` may give you linker errors. If so, add the `lstdc++fs` flag at the end of your compiler's command (be it `clang`, `g++`...).
6. If you're using CMake, there are several things you can do:
- Add the following line near the end of the CMake file (after adding executables):
```c++
target_link_libraries(${PROJECT_NAME} stdc++fs)
```
- Or, add `lstdc++fs` to the CXX flags, for example:
```c++
set(CMAKE_CXX_FLAGS "-std=c++17 -lstdc++fs" )
```
- You could also use `target_link_libraries({PROJECT_NAME} <filesystem lib>)`, replacing the last parameter by the location of your C++ standard filesystem library.

