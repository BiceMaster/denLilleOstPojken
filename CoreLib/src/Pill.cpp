#include "Pill.h"
#include "PillEatenState.h"

Pill::Pill(SpriteInfo* p_spriteInfo, SoundInfo* p_soundInfo, Tile* p_tile, GameStats* p_gameStats): Collectable(p_spriteInfo, p_gameStats)
{
	if (p_gameStats)
		p_gameStats->addPill();

	m_tile = p_tile;
	if (m_tile)
		m_tile->addPill(this);
	m_consumed = false;

	m_eatenState = new PillEatenState(this, p_spriteInfo, p_soundInfo, p_gameStats);
}
Pill::~Pill()
{
	delete m_eatenState;
}
void Pill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	GameObject::update(p_deltaTime, p_inputInfo);
}
bool Pill::isConsumed()
{
	return m_currentState == m_eatenState;
}
void Pill::consume()
{
	switchState(m_eatenState);
}