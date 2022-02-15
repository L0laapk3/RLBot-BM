cmake_minimum_required(VERSION 3.9.4)
project(RLBotBM VERSION 0.1.0)
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CPP_COMPILER clang++)


add_library(RLBotBM STATIC ${source_files})

target_include_directories(RLBotBM PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/lib)
target_compile_features(RLBotBM PUBLIC cxx_std_20)

set_property(TARGET RLBotBM PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_FLAGS "-march=native -D_MT -Xclang --dependent-lib=msvcrt")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g -gcodeview -D_DLL")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-use=${PROJECT_SOURCE_DIR}/tb6.profdata")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack) 
 