	# set OpenCV_DIR from environment variable if not defined
if(NOT Build_For_ANDROID)
	# set OpenCV_DIR from environment variable
	set("OpenCV_DIR" $ENV{OpenCV_DIR})
elseif()
        # set path for OpenCV4Android package
        set("OpenCV_DIR" "$ENV{OpenCV4Android_DIR}/sdk/native/jni")
endif()

# Load settings for an external project (in our case components and modules for opencv)
find_package( OpenCV REQUIRED )

# add opencv include directory to the search path for include files
# so that we will find opencv.h
include_directories(${OpenCV_INCLUDE_DIRS})

# add library
add_library(PriceTagParserLib GlobalParameters.h PriceTagLocalizer.h TextRecognizer.h TextParser.h
PriceTagLocalizer.cpp TextRecognizer.cpp TextParser.cpp)