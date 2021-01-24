cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall")
option(COPY_YOLO "copy yolo binary files to build" ON)

project(capstone)

find_package(OpenCV 4.2.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

file(GLOB PROJECT_SRC src/*.cpp)
include_directories(include)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

# Copy YOLO dir content to build dir
if(COPY_YOLO)
    message("Copying yolo network data. This takes a while...")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/yolo/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(COPY_YOLO)
