cmake_minimum_required(VERSION 3.12)
project(cppcv VERSION 1.0.0)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(lib)
include_directories(app)
include_directories(tests)

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)



