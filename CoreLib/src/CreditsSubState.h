#ifndef CREDITSSUBSTATE_H
#define CREDITSSUBSTATE_H

#include "MenuSubStateInterface.h"
#include "MenuSubStateManager.h"

class CreditsSubState : public MenuSubStateInterface
{
public:
	enum { CR_MAIN, CR_NUM_ITEMS };

	CreditsSubState();
	~CreditsSubState();
	virtual void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager );
	void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager );
};

#endif // CreditsSubState_h__
