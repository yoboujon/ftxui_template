include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.0.2
)

FetchContent_MakeAvailable(ftxui)

set(FTXUI_INCLUDE_DIRS 
    "${ftxui_SOURCE_DIR}/include"
)
