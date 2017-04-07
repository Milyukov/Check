# set minimum required version of CMake
cmake_minimum_required (VERSION 3.4.1)
# name the project
project(PriceTagParserLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(Build_For_ANDROID 0)

# Recurse into the "src" subdirectory. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory(src)	

# Load settings for an external project (in our case components and modules for opencv)
find_package( OpenCV REQUIRED )

# add opencv include directory to the search path for include files
# so that we will find opencv.h
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/src")

# Add executable called main_launcher that is built from the source files
# "main_launcher.cpp".
add_executable (main src/main.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# main_launcher
target_link_libraries (main PriceTagParserLib ${OpenCV_LIBS})
