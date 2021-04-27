# on macos needs to be used with -DCMAKE_CXX_COMPILER=g++ and modern gcc in path, 20210419 XCode does not support concepts

cmake_minimum_required(VERSION 3.10)

project(PSSafeIntTests)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_definitions(NDEBUG)

file(GLOB SOURCES src/*.cpp)

add_executable(PSSafeIntTests ${SOURCES} )

target_include_directories(PSSafeIntTests PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/cute)

enable_testing()

add_test(NAME test COMMAND PSSafeIntTests)