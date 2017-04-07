# set OpenCV_DIR from environment variable if not defined
if(${Build_For_ANDROID})
	# set path for OpenCV4Android package
        set("OpenCV_DIR" "$ENV{OpenCV4Android_DIR}/sdk/native/jni")
elseif()
	# set OpenCV_DIR from environment variable
	set("OpenCV_DIR" $ENV{OpenCV_DIR})        
endif()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "LibConfig.h.in"
  "LibConfig.h"
  )

# Load settings for an external project (in our case components and modules for opencv)
find_package( OpenCV REQUIRED )

# add opencv include directory to the search path for include files
# so that we will find opencv.h
include_directories(${OpenCV_INCLUDE_DIRS})

# add library
if(${Build_For_ANDROID})
	add_library(PriceTagParserLib GlobalParameters.h PriceTagLocalizer.h TextRecognizer.h TextParser.h LibConfig.h
	PriceTagLocalizer.cpp TextRecognizer.cpp TextParser.cpp)
else()
	add_library(PriceTagParserLib GlobalParameters.h PriceTagLocalizer.h TextRecognizer.h TextParser.h LibConfig.h easylogging++.h
	PriceTagLocalizer.cpp TextRecognizer.cpp TextParser.cpp easylogging++.cc)
endif()
