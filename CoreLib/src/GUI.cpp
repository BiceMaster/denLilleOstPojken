#include "GUI.h"
#include "MenuItem.h"
#include <ToString.h>

GUI::GUI(	GameStats* p_stats, vector<SpriteInfo*> p_lives, MenuItem* p_elapsedTime, MenuItem* p_score, 
			MenuItem* p_parTime, MenuItem* p_totalScore, VictoryStruct p_victory, PauseStruct p_pauseData, 
			DefeatStruct p_defeatData, MenuItem* p_buff, MenuItem* p_item, SpriteInfo* p_buffSlot, 
			SpriteInfo* p_itemSlot,	SpriteInfo* p_bombIcon, SpriteInfo* p_speedIcon, ContinueStruct p_continue)
{
	m_totalScore = p_totalScore;
	m_parTime = p_parTime;
	m_stats = p_stats;
	m_lives = p_lives;
	m_elapsedTime = p_elapsedTime;
	m_score = p_score;
	m_buffPowerUp = p_buff;
	m_itemPowerUp = p_item;
	m_buffSlot = p_buffSlot;
	m_itemSlot = p_itemSlot;
	m_bombItem = p_bombIcon;
	m_speedBuff = p_speedIcon;

	m_victoryData = p_victory;
	m_victoryData.victory->getTextArea()->setText("");
	m_victoryData.baseScore->getTextArea()->setText("");
	m_victoryData.multiplier->getTextArea()->setText("");
	m_victoryData.finalScore->getTextArea()->setText("");

	m_pauseData = p_pauseData;
	m_pauseData.paused->getTextArea()->setText("");
	m_pauseData.pressToPlay->getTextArea()->setText("");

	m_defeatData = p_defeatData;
	m_defeatData.cost->getTextArea()->setText("");
	m_defeatData.defeated->getTextArea()->setText("");

	
	m_continue = p_continue;
	m_continue.pressToContinue->getTextArea()->setText("");
	m_continue.pressToEnd->getTextArea()->setText("");
	m_continue.pressToContinue->getTextArea()->animateText(0.2f,2.0f,5.0f,3);
	m_continue.pressToEnd->getTextArea()->animateText(0.2f,2.0f,5.0f,3);

	m_buffSlot->visible = true;
	m_itemSlot->visible = true;
}
GUI::~GUI()
{
	delete m_elapsedTime;
	delete m_buffPowerUp;
	delete m_itemPowerUp;
	delete m_parTime;
	delete m_score;
	delete m_totalScore;

	delete m_victoryData.victory;
	delete m_victoryData.baseScore;
	delete m_victoryData.multiplier;
	delete m_victoryData.finalScore;
	delete m_pauseData.paused;
	delete m_pauseData.pressToPlay;
	
	delete m_defeatData.defeated;
	delete m_defeatData.cost;

	delete m_continue.pressToContinue;
	delete m_continue.pressToEnd;
}
void GUI::update(float p_dt)
{
	for (int i = 2; i >= m_stats->getNumLives(); i--)
		m_lives[i]->visible = false;

	string text = "ELAPSED TIME: " + toString(
		(int)m_stats->getGameTimer()->getElapsedTime());
	m_elapsedTime->getTextArea()->setText(text);

	text = "SCORE      : " + toString(m_stats->getScore());
	m_score->getTextArea()->setText(text);

	text = "PAR TIME    : " + toString((int)m_stats->getParTime());
	m_parTime->getTextArea()->setText(text);

	text = "TOTAL SCORE: " + toString(m_stats->getPreviousScore());
	m_totalScore->getTextArea()->setText(text);

	setSpecialVisible(m_stats->getBuffSlot(),m_speedBuff);
	setSpecialVisible(m_stats->getItemSlot(),m_bombItem);
}
void GUI::setSpecialVisible(Collectable* p_collectable, SpriteInfo* p_special)
{
	if(p_collectable != NULL)
		p_special->visible = true;
	else
		p_special->visible = false;
}
void GUI::showVictory()
{
	m_victoryData.victory->getTextArea()->setText("VICTORY!");
	showContinue();
}
void GUI::showBaseScore(int p_score)
{
	m_victoryData.baseScore->getTextArea()->setText("BASE SCORE: " + toString(p_score));
}
void GUI::showMultiplier(float p_multiplier)
{
	int temp = (int)( p_multiplier * 100 );
	p_multiplier = temp * 0.01f;
	m_victoryData.multiplier->getTextArea()->setText("MULTIPLIER: " + toString(p_multiplier));
}
void GUI::showTotalScore(int p_finalScore)
{
	m_victoryData.finalScore->getTextArea()->setText("FINAL SCORE: " + toString(p_finalScore));
}
void GUI::pause()
{
	m_pauseData.paused->getTextArea()->setText("GAME PAUSED");
	m_pauseData.pressToPlay->getTextArea()->setText("PRESS P TO UNPAUSE");
}
void GUI::unpause()
{
	m_pauseData.paused->getTextArea()->setText("");
	m_pauseData.pressToPlay->getTextArea()->setText("");
}
void GUI::showDefeat()
{
	m_defeatData.defeated->getTextArea()->setText("DEFEAT");
	showEnd();
}
void GUI::showCost()
{
	m_defeatData.cost->getTextArea()->setText("CONTINUE WILL COST HALF YOUR TOTAL SCORE");
}
void GUI::showContinue()
{
	m_continue.pressToContinue->getTextArea()->setText("PRESS ENTER TO CONTIUNE!");
}
void GUI::showEnd()
{
	m_continue.pressToEnd->getTextArea()->setText("PRESS ENTER TO CONTINUE OR ESC TO QUIT!");
}