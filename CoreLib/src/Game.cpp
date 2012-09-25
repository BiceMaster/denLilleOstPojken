#include "Game.h"

Game::Game()
{
}

Game::Game(Timer* p_timer, IOContext* p_context)
{
	m_timer		= p_timer;
	m_running	= false;
	
	if (p_context)
		m_io = new IODevice(p_context);
	else
		m_io = 0;
}

Game::~Game()
{
	if (m_io)
		delete m_io;
}

int Game::run()
{
	if (!m_timer || !m_io)
		return 1;

	m_running = true;
	m_timer->start();


	while (m_running)
	{
		m_timer->tick();
		
		update( (float)m_timer->getDeltaTime(), m_io->fetchInput() );

		if( m_io->fetchInput().keys[InputInfo::ESC] == InputInfo::KEYDOWN)
		{
			m_running = false;
		}

		m_io->draw(m_timer->getDeltaTime());
	}

	return 0;
}

int Game::update(float p_deltaTime, InputInfo p_inputInfo)
{
	for (unsigned int index = 0; index < m_gameObjects.size(); index++)
	{
		m_gameObjects[index].update(p_deltaTime, p_inputInfo);
	}
	return 0;
}