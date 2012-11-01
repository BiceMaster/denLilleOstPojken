#include "GameSettings.h"

GameSettings::GameSettings()
{
	m_scrResX = 1280;
	m_scrResX = 720;

	m_scrStartX = 0;
	m_scrStartY = 0;

	m_windowed = true;
}

int GameSettings::readSettingsFile( string p_filePath )
{
	ifstream file( p_filePath.c_str(), ios::in );

	if( file.good() )
	{
		file>>m_scrResX;
		file>>m_scrResY;

		file>>m_scrStartX;
		file>>m_scrStartY;

		file>>m_windowed;
		return GAME_OK;
	}
	return GAME_FAIL;
}