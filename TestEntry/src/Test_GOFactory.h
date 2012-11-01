#ifndef TESTGOFACTORY_H
#define TESTGOFACTORY_H

#include "Test.h"
#include <GOFactory.h>
#include <TileTypes.h>

class Test_GOFactory: public Test
{
private:
public:
	Test_GOFactory(): Test("GOFACTORY")
	{
	}
	void setup()
	{
		GOFactory factory(NULL);
		
		Avatar* av = factory.CreateAvatar(NULL, NULL, NULL);
		newEntry(TestData("Create Avatar", av != NULL));
		
		Monster* mon = factory.CreateMonster(NULL, NULL, NULL, 300);
		newEntry(TestData("Create Monster", mon != NULL));
		
		Pill* pill = factory.CreatePill(NULL, NULL);
		newEntry(TestData("Create Pill", pill != NULL));

		SuperPill* super = factory.CreateSuperPill(NULL, NULL);
		newEntry(TestData("Create Super Pill", super != NULL));

		SpeedPill* speed = factory.CreateSpeedPill(NULL, NULL);
		newEntry(TestData("Create Speed Pill", speed != NULL));

		MenuItem* menuItem = factory.createMenuItem( 
			fVector3(), fVector2(), "", fVector2() );
		newEntry(TestData("Create Menu Item", menuItem != NULL));

		Switch* goSwitch = factory.CreateSwitch(NULL, NULL, vector<WallSwitch*>(),TileTypes::PATHS);
		newEntry(TestData("Create Switch", goSwitch != NULL));

		Tile* tile = factory.CreateTile(true, TilePosition(0, 0), 10, 10);
		newEntry(TestData("Create Tile", tile != NULL));

		Glyph* glyph = factory.CreateGlyph("../Textures/testglyph.png",0.0f,0.0f,fVector2(8.0f,8.0f));
		newEntry(TestData("Create Glyph", glyph != NULL));

		vector<int> init;
		init.push_back(91);
		Tilemap* map = factory.CreateTileMap(0, 1, 1, init);
		newEntry(TestData("Create Tilemap", map != NULL));

		delete av;
		delete mon;
		delete pill;
		delete super;
		delete speed;
		delete menuItem;
		delete tile;
		delete goSwitch;
		delete map;
		delete glyph;
	}	
};

#endif