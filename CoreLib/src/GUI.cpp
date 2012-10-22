#include "GUI.h"
#include "MenuItem.h"
#include <ToString.h>

GUI::GUI(GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_score, MenuItem* p_parTime, MenuItem* p_totalScore, 
	VictoryStruct p_victory, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_speedIcon, SpriteInfo* p_bombIcon)
{
	m_totalScore = p_totalScore;
	m_parTime = p_parTime;
	m_stats = p_stats;
	m_lives = p_lives;
	m_elapsedTime = p_elapsedTime;
	m_score = p_score;
	m_buffPowerUp = p_buff;
	m_itemPowerUp = p_item;
	m_speedIcon = p_speedIcon;
	m_bombIcon = p_bombIcon;
	m_victoryData = p_victory;
	m_victoryData.victory->getTextArea()->setText("");
	m_victoryData.baseScore->getTextArea()->setText("");
	m_victoryData.multiplier->getTextArea()->setText("");
	m_victoryData.finalScore->getTextArea()->setText("");
}
GUI::~GUI()
{
	delete m_elapsedTime;
	delete m_buffPowerUp;
	delete m_itemPowerUp;
}
void GUI::update(float p_dt)
{
	for (int i = 2; i >= m_stats->getNumLives(); i--)
		m_lives[i]->visible = false;

	string text = "ELAPSED TIME: " + toString((int)m_stats->getGameTimer()->getElapsedTime());
	m_elapsedTime->getTextArea()->setText(text);

	text = "SCORE      : " + toString(m_stats->getScore());
	m_score->getTextArea()->setText(text);

	text = "PAR TIME    : " + toString((int)m_stats->getParTime());
	m_parTime->getTextArea()->setText(text);

	text = "TOTAL SCORE: " + toString(m_stats->getTotalScore());
	m_totalScore->getTextArea()->setText(text);

	if (m_stats->getBuffSlot() == 0)
		m_speedIcon->visible = true;
	else
		m_speedIcon->visible = false;
	if (m_stats->getItemSlot() == 0)
		m_bombIcon->visible = true;
	else
		m_bombIcon->visible = false;
	
}
void GUI::showVictory()
{
	m_victoryData.victory->getTextArea()->setText("VICTORY!");
}
void GUI::showBaseScore(int p_score)
{
	m_victoryData.baseScore->getTextArea()->setText("BASE SCORE: " + toString(p_score));
}
void GUI::showMultiplier(float p_multiplier)
{
	int temp = p_multiplier * 100;
	p_multiplier = temp * 0.01f;
	m_victoryData.multiplier->getTextArea()->setText("MULTIPLIER: " + toString(p_multiplier));
}
void GUI::showTotalScore(int p_finalScore)
{
	m_victoryData.finalScore->getTextArea()->setText("FINAL SCORE: " + toString(p_finalScore));
}