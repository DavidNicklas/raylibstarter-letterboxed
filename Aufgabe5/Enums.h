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

namespace Char
{

    enum Direction {LEFT, RIGHT, UP, DOWN};

}

namespace UI
{

    enum CurrentSortButton {WEIGHT, NAME, COST};
    enum CurrentGameOverOption {PLAY_AGAIN, SHOW_INVENTORY};

}
