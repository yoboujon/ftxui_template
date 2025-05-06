cmake_minimum_required(VERSION 3.22)    #FTXUI asks for CMake 3.22 and C++ 17

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.0.2
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
set(FTXUI_INCLUDE_DIRS 
    "${ftxui_SOURCE_DIR}/include"
)