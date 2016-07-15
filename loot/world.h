#pragma once
#include <stdint.h>
#include "list.h"
#include "Itemtype.h"
#include "TileType.h"

// Chest needs its own file
class Chest
{
private:
    // Any time you think you should be storing any sort of 'type' as an integer:
    // stop yourself,
    // read this: http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html,
    // and promptly create a new file with a nicely defined enum class
    ItemType type;
    int8_t x,y;

public:
    Chest(void) = default;
    Chest(const int8_t x, const int8_t y, const ItemType type); 
    void setType(ItemType type); // I find the presence of only 1 set odd, but oh well
    ItemType getType(void) const;
    int8_t getX(void) const;
    int8_t getY(void) const;
};

using ChestList = List<Chest, 16>;

class World
{
  private:
    uint8_t battleTendency;
  public:
    uint8_t width,height;
    TileType level[128]; //biggest map size, 16*16, 32*8, etc
    ChestList chests;
    uint8_t itemType[16];
    uint8_t itemAction[16]; // I don't even want to know how an arbitrary number is supposed to represent an action

    void init(void);
    void step(void);

    //map stuff
    void load(uint8_t *ID);
    void set(const int8_t x, const int8_t y, const TileType type);
    void setFast(const int8_t x, const int8_t y, const TileType type);
    bool validSize(const uint8_t width, const uint8_t height);
    TileType get(const int8_t x, const int8_t y) const;
    TileType getFast(const int8_t x, const int8_t y) const;
    bool inbound(const int8_t x, const int8_t y) const;

    //battle stuff
    uint8_t getBattleChance(void);

    //item stuff
    void setItem(const uint8_t item, const int8_t x, const int8_t y, const ItemType type);
    ItemType getItemType(const int8_t x, const int8_t y);
    uint8_t getItemID(const int8_t x, const int8_t y);
    // This should be 'hasItem',
    // 'getItem' implies you can actually retrieve a reference to said item
    bool hasItem(const int8_t x, const int8_t y) const;
};
