include_directories("${PROJECT_BINARY_DIR}")

add_executable(Aufgabe1c main.cpp World/Map.cpp World/Map.h GameObject.h RaylibHelp.h World/World.cpp World/World.h UI/Menu.cpp UI/Menu.h Items/BaseItem.cpp Items/BaseItem.h Items/Coffee.cpp Items/Coffee.h)

target_include_directories(Aufgabe1c PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(Aufgabe1c raylib)
