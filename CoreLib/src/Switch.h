#ifndef SWITCH_H
#define SWITCH_H

#include "Tile.h"
#include "Tilemap.h"
#include "Collectable.h"
#include "IODevice.h"

class Switch: public Collectable
{
private:
	Tile* m_tile;
	Tilemap* m_map;
	vector<TilePosition> m_targets;
	float m_cooldown;
public:
	Switch(SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map, GameStats* p_gameStats, vector<TilePosition> p_targets);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif