cmake_minimum_required(VERSION 3.16)
project(tamagotchi CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

add_executable(tamagotchi
    src/main.cpp
    src/Pet.cpp
    src/Cat.cpp
    src/Dog.cpp
    src/Ui.cpp
)

target_include_directories(tamagotchi PRIVATE include ${CURSES_INCLUDE_DIRS})
target_link_libraries(tamagotchi PRIVATE ${CURSES_LIBRARIES})
