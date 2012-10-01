#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SpriteInfo.h"
#include "InputInfo.h"
#include "GameStats.h"

class GameObject
{
protected:
	SpriteInfo*	m_spriteInfo;
	GameStats*	m_gameStats;
public:
	GameObject();
	GameObject(SpriteInfo* p_spriteInfo);
	GameObject(SpriteInfo* p_spriteInfo, GameStats* p_gameStats);
	virtual ~GameObject();

	virtual void update(float p_deltaTime, InputInfo p_inputInfo);
};

#endif