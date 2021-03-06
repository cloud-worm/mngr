

<p align="center">
<img src="images/mngr-logo.png" width="208" height="79" style="text-align: center" />
</p>

<p align="center">
<h3 align="center"> A minimal C++ singe-header library for utility, oriented towards simplicity. </h3>
</p>

<br />

`mngr` is a minimal, single-header C++ library for various aspects of system management & standard library-like utilities, including, for example, file management. `mngr` is oriented towards performance and simplicity. 

Instead of explaining the theory, let us observe a practical example to see just how `mngr` works:

```c++
#include "mngr.hpp"

int main()
{
	mngr::print_and_wait("Hello, World!", 1s);
	
	mngr::print("Creating file Hello.txt:");
	
	mngr::create_file("Hello.txt");
	mngr::add_to_file("Hello.txt", "Hello, World!");
	mngr::wait(300ms);
	
	mngr::print("Hello.txt created!");
}
```

Just **one simple header file** (everything is self-contained within it) that you have to include, and you have access to a quantity of useful data and methods that frees you of having to use complex tokens such as `oftsream`, `data()`, etc. 

This library was created not only for beginners, who may find some C++ concepts difficult and time-consuming, but also for advanced user/professionals who do not wish to waste their time writing tiresome utility functions.

<br /><br />

### Why use `mngr`, exactly?

`mngr` is different from other C++ libraries because its aim is to be as explicit as possible for the user, in such a way that people who use it do not even need to to look at any documentation when writing: the mere names of the different functions are enough to know what code to write.

This means that `mngr` is heavily based on methods and functions, with little to no templates. Each function serves *one* purpose; for example, you cannot create a directory with the `create_file()` function, and you cannot create a file with the `create_folder()` function.

<br /><br />

### How do you use `mngr`?

`mngr` is a single-header library, so you must not install it; instead, you must add `mngr/mngr.hpp` (a self-contained header file) within a project of yours and include it locally.

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

<br /><br />

### Examples of programs with `mngr`

Print and wait
```c++
#include "mngr/mngr.hpp"

int main(int argc, char const *argv[])
{
	mngr::print_and_wait("Hello, World!", 2s);
	mngr::print("Bye!");
	
	return 0;
}
```

Check file existance
```c++
#include "mngr/mngr.hpp"

int main(int argc, char const *argv[])
{
	mngr::print( mngr::file_exists("./foo/bar.txt") );
	
	return 0;
}
```

<br /><br />

### What you can do with `mngr`

```c++
// FILE MANAGEMENT

// Checks if a specific file exists.
bool file_exists(const string &_name);

// Checks if a specific directory exists.
bool folder_exists(const string &_name);

// Creates a file.
void create_file(const string &_name, 
		 const string &content = "", 
		 bool replace = false);
		     
// Deletes a file.
void delete_file(const string &_name);

// Appends content to the end of a file.
void add_to_file(const string &_name, const string &content);

// Gives a new path to a file (can be used for renaming the file, evidently).
void new_path(const string &_name, const string &newpath);

// Deletes a folder.
void delete_folder(const string &_name);

// Creates a folder.
void create_folder(const string &_name);
```
