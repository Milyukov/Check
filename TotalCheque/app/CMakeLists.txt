# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# NB: sort it out
set(TR_SRC "../../LabelParserLib/src")

# add a path to the directory where external lib's CMakeLists.txt is located
add_subdirectory("../../LabelParserLib/src" "../../LabelParserLib/lib")

# set path to OpenCV4Android package
set("OpenCV_DIR" "$ENV{OpenCV4Android_DIR}/sdk/native/jni")

# Load settings for an external project (in our case components and modules for opencv)
find_package( OpenCV REQUIRED )

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             label-parser-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/label-parser-lib-wraper.cpp )

# add opencv include directory to the search path for include files
# so that we will find opencv.h
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("../../LabelParserLib/src")

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       label-parser-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}

                        #
                        LabelParserLib

                        #
                        ${OpenCV_LIBS})