cmake_minimum_required(VERSION 3.29.0)

project("zide")
set(CMAKE_CXX_STANDARD 17)

set(SOURCES 
  src/utils.cpp
  src/theme.cpp
  src/app.cpp
  src/IMGUI/imgui.cpp
  src/IMGUI/imgui_demo.cpp
  src/IMGUI/imgui_draw.cpp
  src/IMGUI/imgui_tables.cpp
  src/IMGUI/imgui_widgets.cpp
  src/IMGUI/imgui_impl_glfw.cpp
  src/IMGUI/imgui_impl_opengl3.cpp
  src/main.cpp
)

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  message ("✅ OPENGL FOUND !!!")
else()
  message (FATAL_ERROR "❌ Cannot find OPENGL")
endif()

#  NOTE:
#  DIRECTORY CONFIGURATIONS
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw-3.4)
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad)

#  NOTE: FINDING GLFW
add_subdirectory(${GLFW_DIR})
include_directories(${GLFW_DIR}/include)

#  NOTE: FINDING GLAD 
add_library(glad STATIC ${GLAD_DIR}/src/glad.c)
include_directories(${GLAD_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/IMGUI)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw glad "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation")
elseif(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw glad ${X11_LIBRARIES} ${CMAKE_DL_LIBS})
endif()
