#pragma once

namespace Items
{

    enum ItemType {EQUIPPABLE, NOT_EQUIPPABLE};

    enum DesiredEquipmentSlot {HAT, HONEY, SHOES};

}

namespace Game
{

    enum TileState {NONE, BLOCKED, PASSABLE, START, EXIT, ITEM};

}
