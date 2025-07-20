cmake_minimum_required(VERSION 3.30)
project(BSP_Entity_Manager)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES
        src/main.cpp
        src/BSP.cpp
        src/BSP.h
        src/Utility.h
)

if(WIN32)
    enable_language(RC)
    set(SOURCES ${SOURCES} resources/resource.rc)
endif()

add_executable(BSP_Entity_Manager ${SOURCES})