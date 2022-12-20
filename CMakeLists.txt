cmake_minimum_required(VERSION 3.24)

project(CACHER LANGUAGES CXX DESCRIPTION "©DHANANJAY SENDAY")

set(CMAKE_CXX_STANDARD 17)

set(FTXUI_BUILD_EXAMPLES OFF CACHE '' INTERNAL FORCE)
string(ASCII 27 ESCAPE)
message("Build Examples Set to ${ESCAPE}[1;31m${FTXUI_BUILD_EXAMPLES}${ESCAPE}[0m ")
set(FTXUI_BUILD_DOCS OFF CACHE "" INTERNAL FORCE)
message("Build Docs Set to ${ESCAPE}[1;31m${FTXUI_BUILD_EXAMPLES}${ESCAPE}[0m ")

add_subdirectory(FTXUI)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        -static-libstdc++
        )