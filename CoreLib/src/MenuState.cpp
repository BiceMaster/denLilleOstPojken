#include "MenuState.h"
#include "StateManager.h"

#include "DebugPrint.h"
#include "ToString.h"

//=========================================================================
// Private Functions
//=========================================================================
void MenuState::nextItem()
{

	if( m_currItemIdx == m_menuItems.size() -1 )
		m_currItemIdx = 0;
	else
		m_currItemIdx++;

	playSound();
}
void MenuState::prevItem()
{
	
	if( m_currItemIdx == 0 )
		m_currItemIdx = m_menuItems.size()-1;
	else
		m_currItemIdx--;

	playSound();
}

bool MenuState::playSound()
{
	if( m_itemSelectSnd != NULL )
	{
		m_itemSelectSnd->play = true;
		return true;
	}
	else
	{
		return false;
	}
}

void MenuState::indentItem( int p_idx, int p_amount )
{
	m_menuItems[p_idx]->setTextOffset((float)p_amount, 0.0f);
}

void MenuState::initMenuItems()
{
	float fw = 1.0f/1920.0f;
	float fh = 1.0f/1080.0f;
	m_bgItem = m_factory->createMenuItem( 
		fVector3( 0.5f, 0.5f, 0.5f ), fVector2( 1.0f, 1.0f ),
		"COPYRIGHT 2012 MAJESTIC 12", fVector2(0.0f, -fh*500.0f),
		fVector2(fw*32, fh*32), "../Textures/SplashScreen.png" );

	string texts[] = {"LEVEL SELECT",  "HIGHSCORE", "CREDITS", "EXIT"};
	for(int i=0; i<4 ; i++ )
	{
		m_menuItems.push_back( m_factory->createMenuItem( 
			fVector3( 0.5f, 0.5f - i*fh*100.0f, 0.9f ), fVector2( fh*600.0f, fh*64.0f ),
			texts[i], fVector2(0.0f, 0.0f), fVector2(fw*32, fh*32),"../Textures/default.png" ));
	}

	m_itemSelectSnd = m_factory->CreateSoundInfo( "../Sounds/Plink_08.wav", 80 );
}

//=========================================================================
// Public Functions
//=========================================================================
MenuState::MenuState(StateManager* p_parent, IODevice* p_io): State(p_parent)
{
	m_io = p_io;
	m_factory = NULL;
	m_itemSelectSnd = NULL;
	m_currItemIdx = 0;
	m_totTime = 0.0f;
}

MenuState::~MenuState()
{
	onExit();
}

bool MenuState::onEntry()
{
	if (!m_resourcesAllocated) // only allocate once
	{
		if (m_io)
		{
			m_factory = new GOFactory(m_io);
			m_io->clearSpriteInfos();
			if (m_factory)
				initMenuItems();
		}
		m_resourcesAllocated = true;
	}
	return true;
}

bool MenuState::onExit()
{
	if (m_resourcesAllocated) // only deallocate if allocated
	{
		if (m_io)
		{
			delete m_bgItem;
			for(unsigned int i = 0; i < m_menuItems.size(); i++)
			{
				delete m_menuItems[i];
			}
			m_menuItems.clear();

			delete m_factory;		
			m_io->clearSpriteInfos();
		}
		//
		m_resourcesAllocated=false;
	}
	return true;
}

void MenuState::update(float p_dt)
{
	m_totTime +=  p_dt;

	float fac = sin(m_totTime*5)*3;
	float fac2 = cos(m_totTime*5)*3;
	m_menuItems[m_currItemIdx]->setTextOffset(fac2, fac);

	if (m_io)
	{
		InputInfo input = m_io->fetchInput();

		// NOTE: The way this function works right now
		// (triggers state change and sprite dealloc), 
		// it has to the last function called in update.
		handleInput(input);
	}

}
void MenuState::draw(float p_dt)
{
}

void MenuState::handleInput(InputInfo p_input)
{

	if(p_input.keys[InputInfo::UP] == InputInfo::KEYPRESSED)
	{
		m_menuItems[m_currItemIdx]->setTextOffset(0.0f, 0.0f);
		prevItem();
	}
	else if (p_input.keys[InputInfo::DOWN] == InputInfo::KEYPRESSED)
	{
		m_menuItems[m_currItemIdx]->setTextOffset(0.0f, 0.0f);
		nextItem();
	}

	if ( p_input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED )
	{
		switch(m_currItemIdx)
		{
		case MI_LEVEL_SELECT:
			m_parent->requestStateChange(m_parent->getInGameState());
			break;
		case MI_EXIT:
			m_parent->terminate();
			break;
		}
	}
	else if( p_input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning() )
	{
		m_parent->terminate();
	}
}
