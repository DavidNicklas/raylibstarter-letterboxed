cmake_minimum_required (VERSION 3.11)

project(Nicklas_David_PortfolioProg2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/raylib.cmake)

# Add config.h.in file
configure_file(config.h.in config.h)

add_subdirectory ("Aufgabe1ab")
add_subdirectory("Aufgabe1c")
add_subdirectory("Aufgabe2a")
add_subdirectory("Aufgabe2b")
add_subdirectory("Aufgabe3a")
add_subdirectory("Aufgabe4")
