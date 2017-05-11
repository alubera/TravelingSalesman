# Traveling Salesman

## Description
This is a project for ACMS 60212 - Advanced Scientic Computing - by John Huber, Andrew Lubera, and Andrew Good. Our project seeks to implement the Traveling Salesman Problem (TSP) in C++ and broadly explore parallel algorithms and heuristics that can be used to best approximate the solution to the problem. 

## Building
CMake was used to build and link the necessary Boost libraries. 

### CRC
If you are on the CRC, CMake 3.6.3 is already installed. Thus, to build, do the following in the root directory: 
```
mkdir build
cd build 
cmake ..
make
```
Note: if cmake is not picking up the right version of gcc, use the flag
```
 -DCMAKE_CXX_COMPILER=/opt/crc/gcc/4.9.2/gcc-4.4.7/bin/g++
```
### OSX
If you are compiling on a local machine using OSX, it will be necessary for you to install CMake first. It is easiest to use homebrew to install CMake. Do the following:
```
brew install cmake
```
### Windows
If you are using a windows machine, you will need to visit https://cmake.org/download/ where there are precompiled binaries for download. 

## Running
After you build the project, you will still be in the build/ directory. To run the executable, do the following:
```
mkdir ../output
cd bin
./main.out
```
## Testing 
We have included the option to run Boost unit tests on our code. We believe that this prevents careless mistakes and increases reproducibility. The test.out executable is automatically build. If you are in the build/ directory, to test, do the following:
```
cd bin
./test.out
```

## Visualization
In order to generate maps, we have provided an R script in the vis/ folder. This script requires the installation of the 'maps' package in R. We recommend running the R script on your local machine rather than on the cluster. 

## Data
The data that we use in this project comes from https://gist.github.com/Miserlou/c5cd8364bf9b2420bb29 and is in JSON format. It contains information, including latitude and longitude coordinates, for the 1,000 most populous cities in the continental United States. 

## Documentation
The code was documented according to the Doxygen style. In order to generate the documentation, do the following:
```
mkdir docs
doxygen Doxyfile
```
Doxygen offers documenation in both html and latex format. These are available as folders in docs.

