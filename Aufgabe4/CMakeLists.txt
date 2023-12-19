include_directories("${PROJECT_BINARY_DIR}")

add_executable(Aufgabe4 main.cpp RaylibHelp.h World/Map.cpp World/Map.h GameObject.h World/World.cpp World/World.h Items/BaseItem.cpp Items/BaseItem.h Items/Coffee.cpp Items/Coffee.h Inventory/Inventory.hpp Inventory/Inventory.h Exceptions/InventoryFull.cpp Exceptions/InventoryFull.h Exceptions/OutOfRange.cpp Exceptions/OutOfRange.h Character/BaseChar.cpp Character/BaseChar.h Character/PlayerChar.cpp Character/PlayerChar.h Items/Equipment/EquippableItem.cpp Items/Equipment/EquippableItem.h Items/Equipment/Shoes.cpp Items/Equipment/Shoes.h Items/Equipment/Hat.cpp Items/Equipment/Hat.h Items/Equipment/Honey.cpp Items/Equipment/Honey.h Sprite.cpp UI/InventoryUI.cpp Items/Steak.cpp Items/Steak.h Exceptions/EquipmentError.cpp Items/Fish.cpp Items/Fish.h Items/Stick.cpp Items/Stick.h World/Tiles.cpp World/Tiles.h Algorithm/AStarPathfinding.h Algorithm/Node.h Algorithm/AStarPathfinding.cpp Helper.h Enums.h World/Path.cpp World/Path.h UI/Menu.cpp UI/Menu.h config.h.in Algorithm/Bubblesort.hpp Algorithm/ItemComparators.hpp)

target_include_directories(Aufgabe4 PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(Aufgabe4 raylib)