cmake_minimum_required (VERSION 3.2)
project(TravelingSalesman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -I$BOOST_ROOT/include -Wno-unused-local-typedefs")

# trying to set an env var so that data can be found without rel path
#execute_process(COMMAND git rev-parse --show-toplevel OUTPUT_VARIABLE GIT_HOME)
#set(ENV{GIT_HOME} GIT_HOME)
#if(ENV{GIT_HOME})
#message(STATUS ${GIT_HOME})
#endif()

# configure a header file to pass some of the CMake settings
# to the source code

include_directories (include)

set(TRAVELINGSALESMAN_HEADERS
		include/Graph.hpp
		include/Node.hpp
		include/Reader.hpp
		)

set(TRAVELINGSALESMAN_SOURCES
		src/main.cpp
		)


set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(main.out ${TRAVELINGSALESMAN_HEADERS}
						${TRAVELINGSALESMAN_SOURCES}
						)

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
