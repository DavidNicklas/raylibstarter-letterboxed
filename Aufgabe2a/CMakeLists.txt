include_directories("${PROJECT_BINARY_DIR}")

add_executable(Aufgabe2a main.cpp World/Map.cpp World/Map.h GameObject.h RaylibHelp.h World/World.cpp World/World.h UI/Menu.cpp UI/Menu.h Items/BaseItem.cpp Items/BaseItem.h Items/Coffee.cpp Items/Coffee.h Inventory/Inventory.hpp Inventory/Inventory.h Exceptions/OutOfRange.h Exceptions/OutOfRange.cpp Exceptions/InventoryFull.h Exceptions/InventoryFull.cpp Items/Equipment/EquippableItem.h Items/Equipment/EquippableItem.cpp Items/Equipment/Hat.cpp Items/Equipment/Honey.cpp Items/Equipment/Shoes.cpp Exceptions/EquipmentError.cpp Exceptions/EquipmentError.h UI/InventoryUI.cpp UI/InventoryUI.h Sprite.cpp Sprite.h Exceptions/SlotIsEmpty.cpp Exceptions/SlotIsEmpty.h Exceptions/UnequipError.cpp Exceptions/UnequipError.h)

target_include_directories(Aufgabe2a PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(Aufgabe2a raylib)