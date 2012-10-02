#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SpriteInfo.h"
#include "InputInfo.h"
#include "GameStats.h"
#include <Vector2.h>
#include <TransformInfo.h>
class GameObject
{
protected:
	SpriteInfo*	m_spriteInfo;
	GameStats*	m_gameStats;
public:
	GameObject();
	GameObject(SpriteInfo* p_spriteInfo);
	GameObject(SpriteInfo* p_spriteInfo, GameStats* p_gameStats);
	virtual			~GameObject();
	virtual void	update(float p_deltaTime, InputInfo p_inputInfo);
	fVector2		getPostion() const;
	float			getRadius() const;
};

#endif
