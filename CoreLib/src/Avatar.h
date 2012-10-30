#ifndef AVATAR_H
#define AVATAR_H

#include "Tilemap.h"
#include "Animation.h"
#include <deque>

class AvatarKilled;
class AvatarJumping;
class AvatarWalking;

struct Direction
{
	enum
	{
		LEFT, RIGHT, DOWN, UP, NONE
	};
};
static TilePosition Directions[4] = 
{
	TilePosition(-1,0), 
	TilePosition(1,0), 
	TilePosition(0,-1), 
	TilePosition(0,1)
};

struct NavigationData
{
	Tile*	m_currentTile;
	Tile*	m_nextTile;
	Tile*	m_queuedTile;

	int		m_direction;
	int		m_desired;

	Tilemap* m_map;
	float dt;
};

class Avatar : public GameObject
{
private:
	NavigationData* m_navigationData;

	AvatarKilled* m_avatarKilledState;
	AvatarJumping* m_avatarJumpingState;
	AvatarWalking*	m_walking;

	Animation* m_currentAnimation;

	float dt;

	float m_avatarOriginalRadius;
	fVector2 m_size;
	float m_offset;

	SpriteInfo* m_shadow;
	deque<Tile*> m_shadowQueue;
	int m_currShadowDir;
	float m_shadowDT;

public:
	Avatar(	SpriteInfo* p_spriteInfo, SpriteInfo* p_shadow, Tilemap* p_map, 
			Tile* p_startTile, GameStats* p_stats, SoundInfo* p_avatarKilledSound, 
			SoundInfo* p_jumpSound);
	virtual ~Avatar();
	void		update(float p_deltaTime, InputInfo p_inputInfo);
	Tile*		getCurrentTile();
	Tile*		getClosestTile();
	int			getDirection();
	float		getTileInterpolationFactor();
	void		setTilePosition(Tile* p_newPosition);
	void		kill();
	bool		inAir();
	bool		isDead();
	void		revive(Tile* p_newPosition);
	void		setCurrentAnimation(Animation* p_animation);
	fVector2	getPostion();
	float		getRadius();
	void		reset();
};

#endif