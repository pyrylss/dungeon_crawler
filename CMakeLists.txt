cmake_minimum_required(VERSION 3.15)
project(DungeonCrawler1)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp)

add_executable(DungeonCrawler1 ${SOURCE_FILES})
find_package(SFML COMPONENTS audio graphics system window)

target_link_libraries(DungeonCrawler1 sfml-graphics sfml-audio sfml-window sfml-system)
