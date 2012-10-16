#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <fstream>
#include <vector>
#include <string>
#include "Tilemap.h"
#include "State.h"
#include "GOFactory.h"


using namespace std;

enum TileType
{
	EMPTY,
	WALL_CENTER,
	PILL,
	AVATAR_SPAWN,
	MONSTER_SPAWN,
	SPEEDPILL,
	SUPERPILL,
	SWITCH,
	TRAP,
	BOMB
};

class MapLoader
{
private:
	Tilemap* m_tileMap;
	vector<GameObject*>	m_gameObjects;
	Avatar*				m_avatar;
	vector<Monster*>	m_monsters;
	vector<Trap*>		m_traps;
	GameStats*			m_stats;
	GUI*				m_gui;
	GOFactory*	m_factory;

public:
	MapLoader();
	virtual ~MapLoader();
	
	int parseMap(string p, IODevice* p_io, GameStats* p_stats, GOFactory* p_factory);
	Tilemap* getTileMap();
	vector<GameObject*> getGameObjects();
	Avatar* getAvatar();
	vector<Monster*> getMonsters();
	vector<Trap*> getTraps();
	GUI*			getGUI();
};

#endif
