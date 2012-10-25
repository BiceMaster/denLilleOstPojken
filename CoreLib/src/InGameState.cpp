#include "InGameState.h"
#include "StateManager.h"
#include "Game.h"
#include <Circle.h>

InGameState::InGameState(StateManager* p_parent, IODevice* p_io, vector<MapData> p_maps, bool p_reset): State(p_parent)
{
	m_io = p_io;
	m_maps = p_maps;
	m_currentMap = 0;
	m_desiredMap = -1;
	m_factory = new GOFactory(m_io);
	m_avatar	= NULL;
	m_gui		= NULL;
	m_tileMap	= NULL;
	m_stats		= NULL;
	m_startTile = NULL;
}
InGameState::~InGameState()
{
	if (m_factory)
	{
		delete m_factory;
		m_factory = NULL;
	}
	onExit();
}
bool InGameState::onEntry()
{
	if (!m_resourcesAllocated)
	{
		if (m_io)
		{
			m_tileMap = NULL;
			m_stats = NULL;
			m_currentMap = 0;
			m_gui = NULL;
			m_parent->getCommonResources()->totalScore = 0;
		}
		restart();
		m_resourcesAllocated=true;
	}
	return true;
}

bool InGameState::onExit()
{
	if (m_resourcesAllocated)
	{
		if (m_io)
		{
			for (int i = m_gameObjects.size() - 1; i >= 0; i--)
			{
				delete m_gameObjects.at(i);
			}
			m_gameObjects.clear();
			if (m_tileMap)
				delete m_tileMap;
			if (m_stats)
				delete m_stats;
			if (m_gui)
				delete m_gui;
		}
		m_resourcesAllocated=false;
	}

	return true;
}

void InGameState::update(float p_dt)
{
	if(m_desiredMap != -1)
	{
		m_currentMap = m_desiredMap;
		m_desiredMap = -1;
		restart();
	}

	if (m_io)
	{
		InputInfo input = m_io->fetchInput();

		if (input.keys[InputInfo::P_KEY] == InputInfo::KEYPRESSED)
		{
			m_paused = !m_paused;
			if (m_paused)
				m_gui->pause();
			else
				m_gui->unpause();
		}
		if (m_paused)
			p_dt = 0;

		if (input.keys[InputInfo::ESC] == InputInfo::KEYRELEASED)
		{
			if (m_stats->getNumLives() > 0)
			{
				m_parent->getCommonResources()->totalScore = 0;
				m_parent->requestStateChange(m_parent->getMenuState());
			}
			else
			{
				m_parent->getCommonResources()->totalScore = m_stats->getPreviousScore();
				m_parent->requestStateChange(m_parent->getGameOverState());
			}
		}
		if (m_stats->getNumPills() < 1 || m_stats->getNumLives() == 0)
		{
			//Victory
			if (m_stats->getNumPills() < 1)
			{
				updateOnVictory(p_dt, input);
			}
			else
			{
				//Defeat
				updateOnDefeat(p_dt, input);
			}
		}
		else
		{
			for (unsigned int index = 0; index < m_gameObjects.size(); index++)
			{
				m_gameObjects[index]->update(p_dt, input);
			};

			checkDynamicCollision();

	
			if (m_stats)
			{
				m_stats->update(p_dt, input);
				if (m_stats->getActivatedItem() == 0)
				{
					Bomb* b = m_factory->CreateBomb(m_avatar->getClosestTile(), m_tileMap); 
					m_bombs.push_back(b);
					m_gameObjects.push_back(b);
				}
			}

			if (m_gui)
				m_gui->update(p_dt);

			int elapsed = (int)m_stats->getGameTimer()->getElapsedTime();

			stringstream ss;

			ss << elapsed;

			string text = "Elapsed Game Time: " + ss.str() + " seconds";

			m_io->setWindowText(text);

			if (m_avatar->isDead())
			{
				m_stats->loseLife();
				if (m_stats->getNumLives() > 0)
				{
					for (int i = 0; i < m_monsters.size(); i++)
					{
						m_monsters[i]->reset();
					}
					m_avatar->revive(m_startTile);
				}


			}
		}
	}
}

void InGameState::draw(float p_dt)
{
}

bool InGameState::checkDynamicCollision()
{
	Circle avatarBC(m_avatar->getPostion(), m_avatar->getRadius() / 4);

	bool collision = false;
	for(unsigned int index = 0; index < m_monsters.size(); index++)
	{
		Monster* monster = m_monsters.at(index);
		if (!monster->isDead())
		{
			Circle monsterBC(monster->getPostion(),monster->getRadius() / 4);

			if(avatarBC.collidesWith(monsterBC))
			{
				collision = true;
				if (m_stats->isSuperMode())
				{
					monster->kill();
					m_stats->addScore(MONSTER_KILLED);
				}
				else
					m_avatar->kill();
			}
		}
		for (int bomb = 0; bomb < m_bombs.size(); bomb++)
		{
			if (m_bombs[bomb]->isColliding(monster) && !monster->isDead())
			{
				monster->kill();
				m_stats->addScore(MONSTER_KILLED);
			}
		}
	}

	for (int bomb = 0; bomb < m_bombs.size(); bomb++)
	{
		if (m_bombs[bomb]->isColliding(m_avatar))
		{
			m_avatar->kill();
		}
	}

	if (!m_avatar->inAir())
	{
		for(unsigned int index = 0; index < m_traps.size(); index++)
		{
			Trap* trap = m_traps.at(index);
			Circle trapBC(trap->getPostion(),trap->getRadius() / 8);

			if(avatarBC.collidesWith(trapBC))
			{
				collision = true;
				m_avatar->kill();
			}
		}
	}

	return collision;
}
void InGameState::restart()
{
	if (m_io)
	{
		m_victoryTime = 0;
		m_defeatTime = 0;
		m_io->clearSpriteInfos();
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			if( m_gameObjects[i] != NULL)
			{
				delete m_gameObjects[i];
				m_gameObjects[i] = NULL;
			}
		}
		m_gameObjects.clear();
		m_monsters.clear();
		m_bombs.clear();
		if (m_tileMap)
		{
			delete m_tileMap;
			m_tileMap = NULL;
		}
		if (m_gui)
		{
			delete m_gui;
			m_gui = NULL;
		}

		m_tileMap	= 0;
		MapLoader mapParser;

		int tscore = 0;
		if (m_stats)
		{
			tscore = m_stats->getTotalScore();
			delete m_stats;
		}
		m_stats = new GameStats(m_parent->getNewTimerInstance(), m_maps[m_currentMap].parTime, tscore);

		stringstream ss;
		ss << m_currentMap;
		string mapString = "../Maps/" + m_maps[m_currentMap].filename;
		mapParser.parseMap(mapString, m_io, m_stats, m_factory);

		m_tileMap = mapParser.getTileMap();
		m_gameObjects = mapParser.getGameObjects();
		m_avatar = mapParser.getAvatar();
		m_monsters = mapParser.getMonsters();
		m_traps = mapParser.getTraps();
		m_gui = mapParser.getGUI();
		m_paused = false;

		if (m_avatar)
			m_startTile = m_avatar->getCurrentTile();
	}
}

int InGameState::setCurrentMap( MapData p_map )
{
	bool found =  false;
	unsigned int idx = 0;
	while( !found && idx<m_maps.size() )
	{
		if(m_maps[idx].filename == p_map.filename)
			found = true;
	}

	if(found)
		return setCurrentMap(idx);
	else
		return GAME_FAIL;
}

int InGameState::setCurrentMap( int p_mapIdx )
{
	if(p_mapIdx < m_maps.size() )
	{
		m_desiredMap = p_mapIdx;
		//restart();
		return GAME_OK;
	}
	else
	{
		return GAME_FAIL;
	}
}

void InGameState::handleInput( InputInfo p_input )
{
	if ( p_input.keys[InputInfo::SPACE] == InputInfo::KEYRELEASED )
	{
		//m_parent->requestStateChange(m_parent->getMenuState());
		restart();
		return;
	}
	else if( p_input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED ||
		!m_io->isRunning() )
	{
		m_parent->terminate();
	}
}
void InGameState::updateOnVictory(float p_dt, InputInfo p_input)
{
	if(p_input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED && m_victoryTime > 3)
	{			
		if (m_currentMap < m_maps.size() - 1)
		{
			m_currentMap = m_currentMap+1;

			if (m_parent->getCommonResources()->unlockedLevels < m_currentMap+1)
			{
				m_parent->getCommonResources()->unlockedLevels = m_currentMap+1;
			}
			restart();
		}
		else
		{
			m_parent->getCommonResources()->totalScore = m_stats->getTotalScore();
			m_parent->requestStateChange(m_parent->getVictoryState());
		}
		return;
	}
	else if (m_victoryTime > 2.4f)
	{
		m_gui->showTotalScore(m_stats->getScore() * m_stats->getMultiplier());
	}
	else if (m_victoryTime > 2.1f)
	{
		m_gui->showMultiplier(m_stats->getMultiplier());
	}
	else if (m_victoryTime > 1.8f)
	{
		m_gui->showBaseScore(m_stats->getScore());
	}
	else if (m_victoryTime > 1.5f)
	{
		m_gui->showVictory();
	}
	m_victoryTime+= p_dt;
	m_io->toneSceneBlackAndWhite(min(m_victoryTime / 1, 1.0f));
}
void InGameState::updateOnDefeat(float p_dt, InputInfo p_input)
{
	m_defeatTime += p_dt;
	m_io->toneSceneBlackAndWhite(min(m_defeatTime / 1, 1.0f));
	
	if(p_input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED && m_defeatTime > 3)
	{
		m_stats->addScore(-m_stats->getScore());
		m_stats->halvePreviousScore();
		restart();
	}
	else if (m_defeatTime > 2.1f)
	{
		m_gui->showContinue();
	}
	else if (m_defeatTime > 1.8f)
	{
		m_gui->showCost();
	}
	else if (m_defeatTime > 1.5f)
	{
		m_gui->showDefeat();
	}
}