#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "IODevice.h"

class Tilemap
{
private:
	Tile**		m_tiles;
	int			m_width;
	int			m_height;
public:
	Tilemap(int p_width, int p_height, Tile** p_tiles);
	virtual ~Tilemap();
	Tile* getTile(TilePosition p_position);
	Tile* closestFreeTile(Tile* p_start);
	bool isValidPosition(TilePosition p_position);
	int getWidth();
	int getHeight();
};

#endif