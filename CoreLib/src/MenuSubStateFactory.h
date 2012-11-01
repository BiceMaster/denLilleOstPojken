
#ifndef MENUSUBSTATEFACTORY_H
#define MENUSUBSTATEFACTORY_H

#include "GOFactory.h"
#include "MenuItem.h"
#include "MenuItemProperties.h"
#include "StateManager.h"

#include "MenuSubStateManager.h"
#include "MenuSubState.h"
#include "MainSubState.h"
#include "LevelSelectSubState.h"
#include "HighscoreSubState.h"
#include "CreditsSubState.h"
#include "ExitSubState.h"
#include <vector>
#include <string>
#include "HighScore.h"

using namespace std;

class MenuSubStateManager;
class MenuSubState;

class MenuSubStateFactory
{
private:
	GOFactory* m_gof;
	MenuSubStateManager* m_manager;

	string m_menuBackSoundPath;
	string m_navigationSoundPath;
	string m_itemSelectSoundPath;

public:
	MenuSubStateFactory( GOFactory* p_gof, MenuSubStateManager* p_manager );
	~MenuSubStateFactory();

	MenuSubState* createMain();
	vector<string> createMainTexts();
	MenuItemProperties createMainProperties();

	MenuSubState* createLevelSelect( vector<MapData> p_maps, int p_numUnlockedLevels );
	vector<string> createLevelSelectTexts( vector<MapData> p_maps, int p_numUnlockedLevels );
	MenuItemProperties createLevelSelectProperties();

	MenuSubState* createHighscore();
	vector<string> createHighscoreTexts();
	MenuItemProperties createHighscoreProperties();

	MenuSubState* createCredits();
	vector<string> createCreditsTexts();
	MenuItemProperties createCreditsProperties();

	MenuSubState* createExit();
	vector<string> createExitTexts();
	MenuItemProperties createExitProperties();

	vector<MenuItem*> createItems( MenuItemProperties p_properties,
		vector<string> p_texts );
	MenuSubState* createMenuSubState();
	
};
#endif // MENUSUBSTATEFACTORY_H