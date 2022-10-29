cmake_minimum_required(VERSION 3.9.4)
project(RLBotBM VERSION 0.1.0)

option(BUILD_SHARED "Build as a library" ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)

if (BUILD_SHARED)
	add_library(${PROJECT_NAME} SHARED ${source_files})
else()
	add_library(${PROJECT_NAME} STATIC ${source_files})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g -gcodeview -D_DLL")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack) 
 