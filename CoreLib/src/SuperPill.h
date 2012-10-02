#ifndef SUPERPILL_H
#define SUPERPILL_H

#include "Tile.h"
#include "Collectable.h"

class SuperPill : public Collectable
{
private:
	Tile* m_tile;
	bool m_eaten;
public:
	SuperPill(IODevice* p_io, Tile* p_tile, GameStats* p_gameStats);
	~SuperPill();
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif