#include "Tilemap.h"

Tilemap::Tilemap(int p_width, int p_height)
{
	m_width = p_width;
	m_height = p_height;

	m_tiles = new Tile*[p_width * p_height];
	for (int row = 0; row < p_height; row++)
	{
		for (int col = 0; col < p_width; col++)
			m_tiles[row * p_height + col] = new Tile(FREE_TILE, TilePosition(col, row));
	}
}
Tilemap::Tilemap(int p_width, int p_height, TileType* p_initData)
{
	m_width = p_width;
	m_height = p_height;

	m_tiles = new Tile*[p_width * p_height];
	for (int row = 0; row < p_height; row++)
	{
		for (int col = 0; col < p_width; col++)
			m_tiles[row * p_height + col] = new Tile(p_initData[row * p_height + col], TilePosition(col, row));
	}
}
Tilemap::~Tilemap()
{
	for (int i = 0; i < m_width * m_height; i++)
	{
		delete m_tiles[i];
	}
	delete[] m_tiles;
}
Tile* Tilemap::getTile(TilePosition p_position)
{
	if (!isValidPosition(p_position))
		return 0;

	return m_tiles[p_position.y * m_height + p_position.x];
}
Tile* Tilemap::closestFreeTile(Tile* p_start)
{
	TilePosition min = p_start->getPosition() - TilePosition(1, 1);
	TilePosition max = p_start->getPosition() + TilePosition(1, 1);

	while (min.x >= 0 || min.y >= 0 || max.x < m_width || max.y < m_height)
	{
		for (int row = min.y; row <= max.y; row++)
		{
			for (int col = min.x; col <= max.x; col++)
			{
				if (row == min.y || row == max.y || col == min.x || col == max.x)
				{
					Tile* t = getTile(TilePosition(col, row));
					if (t && t->isFree())
						return t;
				}
			}
		}
		min = min - TilePosition(1, 1);
		max = max + TilePosition(1, 1);
	}
	return 0;
}
bool Tilemap::isValidPosition(TilePosition p_position)
{
	if (p_position.x < 0 || p_position.x >= m_width)
		return false;
	if (p_position.y < 0 || p_position.y >= m_height)
		return false;
	return true;
}