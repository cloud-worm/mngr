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

### Why use `nmngr`, exactly?

`mngr` is different from other C++ libraries because its aim is to be as explicit as possible for the user, in such a way that people who use it do not even need to to look at any documentation when writing: the mere names of the different functions are enough to know what code to write.

This means that `mngr` is heavily based on methods and functions, with little to no templates. Each function serves *one* purpose; for example, you cannot create a directory with the `create_file()` function, and you cannot create a file with the `create_folder()` function.
