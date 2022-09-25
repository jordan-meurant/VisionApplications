cmake_minimum_required(VERSION 3.23)
project(VisionApplications)

set(CMAKE_CXX_STANDARD 14)

add_executable(VisionApplications main.cpp)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

target_link_libraries(VisionApplications ${OpenCV_LIBS})

set (CMAKE_PREFIX_PATH "usr/local/Cellar/qt/6.3.1_4/lib/cmake")
find_package(Qt6Widgets REQUIRED)

target_link_libraries(VisionApplications Qt6::Widgets)
