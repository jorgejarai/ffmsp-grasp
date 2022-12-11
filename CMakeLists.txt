cmake_minimum_required(VERSION 3.10)

project(ffmsp)

add_subdirectory(3rdparty/argumentum)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)

    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)

        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()

        unset(flag_supported CACHE)
    endif()
endfunction()

enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-pedantic")

include_directories(include)
include_directories(3rdparty/argumentum/include)

add_executable(ils src/main.cpp src/ffmsp.cpp src/grasp.cpp src/greedy.cpp
    src/timer.cpp src/rng.cpp src/ils.cpp)
target_link_libraries(ils argumentum)
add_dependencies(ils argumentum)
