cmake_minimum_required(VERSION 3.25)
project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADER_FILES "Source/*.h")
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Base)

