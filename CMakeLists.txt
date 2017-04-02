cmake_minimum_required (VERSION 3.2)
project(TravelingSalesman)

set(CMAKE_CXX_STANDARD 14)


# configure a header file to pass some of the CMake settings
# to the source code

include_directories (include)

set(TRAVELINGSALESMAN_HEADERS
		include/Graph.hpp
		)

set(TRAVELINGSALESMAN_SOURCES
		src/main.cpp
		)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(main.out ${TRAVELINGSALESMAN_HEADERS}
						${TRAVELINGSALESMAN_SOURCES}
						)

SET (BOOST_ROOT "/afs/crc.nd.edu/x86_64_linux/scilib/boost/boost_1_54_0")
SET (BOOST_MIN_VERSION "1.54.0")
SET (Boost_NO_BOOST_CMAKE ON)
FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED)
if (NOT Boost_FOUND)
  message(FATAL_ERROR "Fatal error: Boost (version >= 1.55) required.")
else()
  message(STATUS "Setting up BOOST")
  message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
  message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif (NOT Boost_FOUND)

target_link_libraries (main.out ${Boost_LIBRARIES})


find_package(Boost REQUIRED
			COMPONENTS 
				unit_test_framework )

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${CMAKE_BINARY_DIR}/lib)

set(TEST_SOURCES
	test/TravelingSalesman_test.cpp)

add_executable(test.out ${TRAVELINGSALESMAN_HEADERS} ${TEST_SOURCES})
target_link_libraries(test.out ${Boost_LIBRARIES})
add_test(NAME test.out 
		 COMMAND ${CMAKE_BINARY_DIR}/bin/test.out)
