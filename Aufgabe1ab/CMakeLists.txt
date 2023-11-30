include_directories("${PROJECT_BINARY_DIR}")

add_executable(Aufgabe1ab main.cpp World/Map.cpp World/Map.h GameObject.h RaylibHelp.h World/World.cpp World/World.h UI/Menu.cpp UI/Menu.h)

target_include_directories(Aufgabe1ab PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(Aufgabe1ab raylib)
