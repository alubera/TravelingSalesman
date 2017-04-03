# Traveling Salesman

## Description
This is a project for ACMS 60212 - Advanced Scientic Computing - by John Huber, Andrew Lubera, and Andrew Good. Our project seeks to implement the Traveling Salesman Problem (TSP) in C++ and broadly explore parallel algorithms and heuristics that can be used to best approximate the solution to the problem. 

## Building
CMake was used to build and link the necessary Boost libraries. If you are on the CRC, CMake 3.6.3 is already installed. Thus, to build, do the following in the root directory: 
```
mkdir build
cd build 
cmake ..
make
```

If you are compiling on a local machine, it will be necessary for you to install CMake first. Then, follow the above steps. 

## Running
After you build the project, you will still be in the build/ directory. To run the executable, do the following:
```
cd bin
./main.out
```
## Testing 
We have included the option to run Boost unit tests on our code. We believe that this prevents careless mistakes and increases reproducibility. The test.out executable is automatically build. If you are in the build/ directory, to test, do the following:
```
cd bin
./test.out
```
## Data
The data that we use in this project comes from https://gist.github.com/Miserlou/c5cd8364bf9b2420bb29 and is in JSON format. It contains information, including latitude and longitude coordinates, for the 1,000 most populous cities in the continental United States. 

