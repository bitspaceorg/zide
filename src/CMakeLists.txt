set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(APP_DIR "${SRC_DIR}/app")
set(GFX_DIR "${SRC_DIR}/gfx")
set(TOOLS_DIR "${SRC_DIR}/tools")
set(UI_DIR "${SRC_DIR}/ui")
set(UTILS_DIR "${SRC_DIR}/utils")

file(GLOB APP_SOURCES "${APP_DIR}/*.cpp")
file(GLOB GFX_SOURCES "${GFX_DIR}/*.cpp")
file(GLOB TOOLS_SOURCES "${TOOLS_DIR}/*.cpp")
file(GLOB UI_SOURCES "${UI_DIR}/*.cpp")
file(GLOB UTILS_SOURCES "${UTILS_DIR}/*.cpp")

include_directories(
    ${APP_DIR}
    ${GFX_DIR}
    ${TOOLS_DIR}
    ${UI_DIR}
    ${UTILS_DIR}
)

add_executable(${PROJECT_NAME}
    zide.cpp
    ${APP_SOURCES}
    ${GFX_SOURCES}
    ${TOOLS_SOURCES}
    ${UI_SOURCES}
    ${UTILS_SOURCES}
)
