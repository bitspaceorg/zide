cmake_minimum_required(VERSION 3.28.0)

project(nativefiledialog)

# Create a static library from the NativeFileDialog source files
add_library(nativefiledialog STATIC)

# Set the C++ standard
set_property(TARGET nativefiledialog PROPERTY CXX_STANDARD 11)

# Define the source files based on the platform
set(SOURCES src/nfd_common.c)
set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# Add platform-specific files
if(APPLE)
    list(APPEND SOURCES src/nfd_cocoa.m)
elseif(WIN32)
    list(APPEND SOURCES src/nfd_win.cpp)
elseif(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

    list(APPEND SOURCES src/nfd_gtk.c)
    list(APPEND INCLUDE_DIRS ${GTK3_INCLUDE_DIRS})
    list(APPEND LIBRARIES ${GTK3_LIBRARIES})
endif()

# Add sources, include directories, and link necessary libraries
target_sources(nativefiledialog PRIVATE ${SOURCES})
target_include_directories(nativefiledialog PUBLIC ${INCLUDE_DIRS})
target_link_libraries(nativefiledialog PRIVATE ${LIBRARIES})
