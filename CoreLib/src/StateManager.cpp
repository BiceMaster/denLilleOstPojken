#include "StateManager.h"

StateManager::StateManager()
{
	m_inGameState = new InGameState(this);
	m_menuState = new MenuState(this);
	m_currentState = m_desiredState = m_menuState;
}
void StateManager::requestStateChange(State* p_newState)
{
	m_desiredState = p_newState;
}

void StateManager::update(float p_dt)
{
	if (m_desiredState != m_currentState)
	{
		switchState();
	}
	m_currentState->update(p_dt);
}
void StateManager::draw(float p_dt)
{
	m_currentState->draw(p_dt);
}

State* StateManager::getCurrentState()
{
	return m_currentState;
}
State* StateManager::getMenuState()
{
	return m_menuState;
}
State* StateManager::getInGameState()
{
	return m_inGameState;
}

void StateManager::switchState()
{
	m_currentState = m_desiredState;
}