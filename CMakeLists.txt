cmake_minimum_required(VERSION 3.16)
project(bnet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Simulator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Channel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/node/Buoy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/node/BuoyArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol/Scheduler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol/Beacon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base/Random.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base/ConfigLoader.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_compile_definitions(${PROJECT_NAME} PRIVATE CONF_PATH="${CMAKE_CURRENT_SOURCE_DIR}/bnet.ini")
