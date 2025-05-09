cmake_minimum_required(VERSION 3.18)
project(
  ftxui_template
  DESCRIPTION "FTXUI Template Project"
  HOMEPAGE_URL "https://www.etheryo.fr/"
  LANGUAGES CXX C
)
set(CMAKE_CXX_STANDARD 17)  # Because using std::any, ftxui uses C++17 too.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Dependencies
include(dependencies.cmake)

set(TARGET ftxui_template)
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(${TARGET}
    ${SRC}/ui.cpp
    ${SRC}/logger.cpp
    ${SRC}/event.cpp
    # Pages
    ${SRC}/pages/page1.cpp
    ${SRC}/pages/page2.cpp
    # Main
    ${SRC}/main.cpp
)

# Include folders
target_include_directories(${TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${TARGET} PRIVATE "${FTXUI_INCLUDE_DIRS}")

# Libraries
target_link_libraries(
    ${TARGET} PRIVATE
    component
    dom
    screen
)

# Output folder
set_target_properties(${TARGET}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
