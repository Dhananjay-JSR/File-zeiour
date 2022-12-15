cmake_minimum_required(VERSION 3.24)
project(CACHER LANGUAGES CXX DESCRIPTION "©DHANANJAY SENDAY")

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(FTXUI)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
        )