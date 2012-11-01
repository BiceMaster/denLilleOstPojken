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
	m_victoryData.victory->getTextArea()->setVisible(false);
	m_victoryData.baseScore->getTextArea()->setVisible(false);
	m_victoryData.multiplier->getTextArea()->setVisible(false);
	m_victoryData.finalScore->getTextArea()->setVisible(false);
	m_victoryData.finalScore->getTextArea()->setVisible(false);

	m_pauseData = p_pauseData;
	m_pauseData.paused->getTextArea()->setVisible(false);
	m_pauseData.pressToPlay->getTextArea()->setVisible(false);

	m_defeatData = p_defeatData;
	m_defeatData.cost->getTextArea()->setVisible(false);
	m_defeatData.defeated->getTextArea()->setVisible(false);

	
	m_continue = p_continue;
	m_continue.pressToContinue->getTextArea()->setVisible(false);
	m_continue.pressToEnd->getTextArea()->setVisible(false);

	m_buffSlot->visible = true;
	m_itemSlot->visible = true;

	m_lastIterationScore = 0;
	m_scoreShakeAccumulated = 0.0f;
	m_scoreShakeDecayFactor = 50.0f;
	m_scoreShakeMult = 0.3f;

	m_timeShakeTime = 10.0f;
	m_timeShakeMult = 10.0f;
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
void GUI::update(float p_dt, InputInfo p_input)
{
	for (int i = 2; i >= m_stats->getNumLives(); i--)
		m_lives[i]->visible = false;

	// Shake elapsed time when close to par time
	float parTime = (float)m_stats->getParTime();
	float elapsedTime = (float)m_stats->getGameTimer()->getElapsedTime();
	float timeDiff = parTime - elapsedTime;
	float timeShake = (1.0f - timeDiff/m_timeShakeTime)*m_timeShakeMult;

	string text = "ELAPSED TIME: " + toString( (int)elapsedTime );
	m_elapsedTime->getTextArea()->setText(text);
		m_elapsedTime->update( p_dt, p_input );
	if( 0.0f < timeDiff && timeDiff < m_timeShakeTime )
	{
		m_elapsedTime->animateText( 0.01f, timeShake, 10.0f, 4 );
	}

	text = "PAR TIME    : " + toString( (int)parTime );
	m_parTime->getTextArea()->setText(text);

	// Score shake calculation
	int newScore = m_stats->getScore();
	int scoreDiff = newScore - m_lastIterationScore;
	m_lastIterationScore = newScore;
	m_scoreShakeAccumulated += ( (float)scoreDiff * m_scoreShakeMult );
	m_scoreShakeAccumulated -= ( m_scoreShakeDecayFactor*p_dt );
	if( m_scoreShakeAccumulated < 1.0f )
		m_scoreShakeAccumulated = 0.0f;

	text = "SCORE      : " + toString( newScore );
	m_score->getTextArea()->setText( text );
	m_score->update( p_dt, p_input );
	m_score->animateText( 0.01f, m_scoreShakeAccumulated, 10.0f, 4 );

	text = "TOTAL SCORE: " + toString(m_stats->getPreviousScore());
	m_totalScore->getTextArea()->setText(text);

	setSpecialVisible(m_stats->getBuffSlot(),m_speedBuff);
	setSpecialVisible(m_stats->getItemSlot(),m_bombItem);

	if(m_continue.pressToEnd->getTextArea()->getVisible() || m_continue.pressToContinue->getTextArea()->getVisible())
	{
		m_continue.pressToEnd->update( p_dt, p_input );
		m_continue.pressToContinue->update( p_dt, p_input );
		
		m_continue.pressToContinue->animateText(0.02f,2.0f,15.0f,2);
		m_continue.pressToEnd->animateText(0.05f,2.0f,15.0f,2);
	}
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
	m_victoryData.victory->getTextArea()->setVisible(true);
	showContinue();
}
void GUI::showBaseScore(int p_score)
{
	m_victoryData.baseScore->getTextArea()->setText("BASE SCORE: " + toString(p_score));
	m_victoryData.baseScore->getTextArea()->setVisible(true);
}
void GUI::showMultiplier(float p_multiplier)
{
	int temp = (int)( p_multiplier * 100 );
	p_multiplier = temp * 0.01f;
	m_victoryData.multiplier->getTextArea()->setText("MULTIPLIER: " + toString(p_multiplier));
	m_victoryData.multiplier->getTextArea()->setVisible(true);
}
void GUI::showTotalScore(int p_finalScore)
{
	m_victoryData.finalScore->getTextArea()->setText("FINAL SCORE: " + toString(p_finalScore));
	m_victoryData.finalScore->getTextArea()->setVisible(true);
}
void GUI::pause()
{
	m_pauseData.paused->getTextArea()->setVisible(true);
	m_pauseData.pressToPlay->getTextArea()->setVisible(true);
}
void GUI::unpause()
{
	m_pauseData.paused->getTextArea()->setVisible(false);
	m_pauseData.pressToPlay->getTextArea()->setVisible(false);
}
void GUI::showDefeat()
{
	m_defeatData.defeated->getTextArea()->setVisible(true);
	showEnd();
}
void GUI::showCost()
{
	m_defeatData.cost->getTextArea()->setVisible(true);
}
void GUI::showContinue()
{
	m_continue.pressToContinue->getTextArea()->setVisible(true);
}
void GUI::showEnd()
{
	m_continue.pressToEnd->getTextArea()->setVisible(true);
}