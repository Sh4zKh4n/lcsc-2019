# Getting started with C++<a id="sec-1"></a>

## Development environment<a id="sec-1-1"></a>

### Windows<a id="sec-1-1-1"></a>

1.  Download and install Notepad++
2.  Download and install CygWin (https://www.cygwin.com/). In the installation process, install `gcc` and `g++` from the 'Devel' category.
3.  Open Notepad++ and make a file `main.cpp`. Save in e.g. `My Documents\LCSC\`. Open CygWin and change to the correct directory.

### Linux<a id="sec-1-1-2"></a>

1.  Download and install `gedit`:
    
    ```bash
    # ubuntu
    sudo apt-get install gedit
    # fedora
    sudo dnf install gedit
    ```
2.  Install GCC
    
    ```bash
    # ubuntu
    sudo apt install build-essential
    # fedora
    sudo dnf install gcc gcc-c++
    ```
3.  Open gedit, and make a file called `main.cpp`, save this in e.g. `~/lcsc/`. Open a terminal, and change to the correct directory:
    
    ```
    cd ~/lcsc/
    ```

## Writing and compiling a basic program<a id="sec-1-2"></a>

You should now have one text editor open with a file `main.cpp` (the *source*), and one terminal window that we will use to compile.

First, we write a simple 'Hello, world!' program.

```cpp
#include <iostream>

int main() {
  std::cout << "Hello, world!\n";
  return 0;
}
```

Then, we compile and run this program using the terminal.

```bash
g++ main.cpp -o main
./main
```

## Writing and compiling a simple RNG<a id="sec-1-3"></a>

Replace (or make a new file) your source file with the following:

```cpp
#include <iostream>

int rng(unsigned int previous) {
  return (100 * previous + 5) % 23;
}

int main() {
  unsigned int x = 5;
  for (int i = 0; i < 10; ++i) {
    x = rng(x);
    std::cout << x << "\n";
  }
  return 0;
}
```
