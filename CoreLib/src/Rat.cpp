#include "Rat.h"

Rat::Rat(GameStats* p_gameStats, SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map,
					SoundInfo* p_monsterKilledSound)
	: Monster(p_gameStats, p_spriteInfo)
{
	dt = 0;
	m_startTile = m_currentTile = m_nextTile = p_tile;
	m_map = p_map;
	m_respawning = false;
	m_dead = false;
	m_ai = NULL;

	m_monsterKilledSound = p_monsterKilledSound;

	m_right = new Animation(fVector2(0, 0), 64, 64, 4, 0.1f, true);
	m_left = new Animation(fVector2(0, 64), 64, 64, 4, 0.1f, true);
	m_down = new Animation(fVector2(0, 128), 64, 64, 4, 0.1f, true);
	m_up = new Animation(fVector2(0, 192), 64, 64, 4, 0.1f, true);

	m_currentAnimation = m_down;
	m_timeSinceSpawn = 0;
	m_size = fVector2(p_spriteInfo->transformInfo.scale[TransformInfo::X],
						p_spriteInfo->transformInfo.scale[TransformInfo::Y]);
}
Rat::~Rat()
{
}
void Rat::update(float p_deltaTime, InputInfo p_inputInfo)
{
	m_timeSinceSpawn += p_deltaTime;
	if (!m_dead && m_timeSinceSpawn > SPAWNTIME)
	{
		if (m_ai)
			m_ai->update(p_deltaTime);

		dt += p_deltaTime * 6;
		while (dt > 1)
		{
			dt -= 1;
			if (m_currentTile)
			{
				m_currentTile = m_nextTile;
				if (m_path.size() > 0)
				{
					if (m_path.back()->isFree())
					{
						m_nextTile = m_path.back();
						m_path.pop_back();
					}
					else
					{
						m_path.clear();
					}
				}
				else
				{
					m_ai->findTarget();

					if(m_path.size() == 0)
					{
						Tile* t;
						do
						{
							int rndX = rand() % m_map->getWidth();
							int rndY = rand() % m_map->getHeight();
							t = m_map->getTile(TilePosition(rndX, rndY));					
						} while (!t->isFree());

						FindPath(m_currentTile, t);
					}
				}
			}
		}
	}
	if(m_spriteInfo)
	{
		determineAnimation();
		transformSpriteInformation();

		if (m_currentAnimation)
		{
			if (m_currentTile != m_nextTile)
				m_currentAnimation->update(p_deltaTime);
			m_spriteInfo->textureRect = m_currentAnimation->getCurrentFrame();
		}

		if (m_timeSinceSpawn < SPAWNTIME)
		{
			float frac = m_timeSinceSpawn / SPAWNTIME;
			m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_size.x * frac;
			m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_size.y * frac;
		}
	}
	else if (m_respawning)
	{
		//DO VISUALFEEBACK - DONE NOW!! MOAHAHAHAAHA ANTON WAS HERE
	}
}
void Rat::reset()
{
	Monster::reset();
	m_timeSinceSpawn = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::X] = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::Y] = 0;
}
void Rat::beginRespawn()
{
	Monster::beginRespawn();
	m_timeSinceSpawn = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::X] = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::Y] = 0;
}