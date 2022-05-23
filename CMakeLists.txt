cmake_minimum_required(VERSION 3.10)

project(kcinteger)


add_library(kcinteger
    include/kcinteger/primitive.h
    src/kcinteger/primitive.cpp
)

target_include_directories(kcinteger PUBLIC include)

add_executable(kcitest 
    test/kciunit/kcimain.cpp
)

target_include_directories(kcitest PUBLIC include)
target_link_libraries(kcitest PUBLIC kcinteger)
