cmake_minimum_required(VERSION 3.25)
project(sillylib VERSION 1.0 LANGUAGES CXX C)

if(NOT MSVC)
    message(FATAL_ERROR "sillylib only supports the MSVC compiler.")
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Available build types" FORCE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

add_library(SillylibProjectWarnings INTERFACE)
target_compile_options(SillylibProjectWarnings INTERFACE /W4 /WX)
add_compile_options(/MP)

add_subdirectory(vendor)
include(projects.cmake)
