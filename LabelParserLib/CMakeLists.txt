# set minimum required version of CMake
cmake_minimum_required (VERSION 3.7)
# name the project
project(LabelParserLib)

set (Build_For_ANDROID 1)

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
target_link_libraries (main LabelParserLib ${OpenCV_LIBS})


# create a list of files to copy (Debug or Release)
set( THIRD_PARTY_DLLS
   ${OpenCV_DIR}/bin/Debug/opencv_core320d.dll
   ${OpenCV_DIR}/bin/Debug/opencv_imgcodecs320d.dll
   ${OpenCV_DIR}/bin/Debug/opencv_imgproc320d.dll
   ${OpenCV_DIR}/bin/Debug/opencv_highgui320d.dll
   ${OpenCV_DIR}/bin/Debug/opencv_videoio320d.dll
   #${OpenCV_DIR}/bin/Release/opencv_core320.dll
   #${OpenCV_DIR}/bin/Release/opencv_imgcodecs320.dll
   #${OpenCV_DIR}/bin/Release/opencv_imgproc320.dll
   #${OpenCV_DIR}/bin/Release/opencv_highgui320.dll
   #${OpenCV_DIR}/bin/Release/opencv_videoio320.dll
)

# do the copying
foreach( file_i ${THIRD_PARTY_DLLS})
    add_custom_command(
    TARGET main                                              # Adds a post-build event to main_launcher
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_if_different         			     # which executes "cmake - E copy_if_different..."
        ${file_i}                                            # <--this is in-file
        $<TARGET_FILE_DIR:main>
)
endforeach( file_i )