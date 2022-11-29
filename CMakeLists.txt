cmake_minimum_required(VERSION 3.9.4)
project(RLBot-BM VERSION 0.1.0)

option(BUILD_DLL "Build dynamic library instead of static one" OFF)
option(ENABLE_IPO "Controls link time optimization" ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)

if (BUILD_DLL)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Xclang --dependent-lib=msvcrt")
	add_library(${PROJECT_NAME} SHARED ${source_files})
else()
	add_library(${PROJECT_NAME} STATIC ${source_files})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION ENABLE_IPO)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g -gcodeview -D_DLL")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack) 
