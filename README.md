# IReflx
A library and application to redirect an UDP/IP stream to a different socket address.

## Project Structure
The __IReflx__ project composed of a static library and a console application.

### Static Library (IReflx)
The static library __IReflx__ implements the functionality to redirect a transmitted UDP/IP stream to a different socket address.
The source files are located in the `IReflx` folder.

### Console Application (IReflxApp)
The console application __IReflxApp__ is an executable and provides a command line interface to the __IReflx__ library.  The source file for the main program is located under the `src` folder.

## How to Build on Windows

This project uses CMake to generate a build environment, build, and install the __IReflxApp__ application. Do the following steps:
```
cmake -S . -B ./build -A x64
```
```
cmake --build ./build
```
Before you install __IReflxApp__, ensure you open the console in Administrator mode.
```
cmake --install ./build
```

## How to Build on Linux

This project uses CMake to generate a build environment, build, and install the __IReflxApp__ application. Do the following steps:
```
cmake -S . -B ./build
```
```
cmake --build ./build
```
```
sudo cmake --install ./build
```

## Usage
The __IReflxApp__ usage is as follows:

```
Usage: IReflxApp <OPTIONS>

Options:
  -s    Source socket address; otherwise, stdin.
  -d    Destination socket address; otherwise, stdout.
  -t    Time to Live. (default: 16)
  -i    Specifies the network interface IP address for the source stream.
  -o    Specifies the network interface IP address for the destination stream.
  -?    Print this message.
```
### Example 1
Redirect a transmitted UDP/IP stream to a new socket address.
 ```
IReflxApp -s 239.3.1.11:50000 -d 192.168.0.24:50001
```

### Example 2
Redirect a transmitted UDP/IP stream to a pipe that is an input to another application.

```
IReflxApp -s 239.3.1.11:50000 | AnotherApp.exe
```

### Example 3 
Read a pipe as an input and stream it.

```
SomeApp.exe | IReflxApp -d 239.3.1.11:50000
```
