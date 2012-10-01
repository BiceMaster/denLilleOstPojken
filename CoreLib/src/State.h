#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Timer.h"
#include "IOContext.h"
#include "InputInfo.h"
#include "IODevice.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Pill.h"
#include "Monster.h"
#include "LoadMap.h"
#include "Avatar.h"
#include <ctime>

class StateManager;

class State
{
protected:
	StateManager* m_parent;
public:
	State(StateManager* p_parent);
	virtual void update(float p_dt) = 0;
	virtual void draw(float p_dt) = 0;
};

#endif