<p align="center">
<img src="images/mngr-logo.png" width="208" height="79" style="text-align: center" />
</p>

### A minimal C++ library for system management, oriented towards simplicity.

`mngr` is a minimal C++ library for various aspects of system management, including, for example, file management. mngr is oriented towards peformance and simplicity. 

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
