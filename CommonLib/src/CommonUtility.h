#ifndef COMMONUTILITY_H
#define COMMONUTILITY_H

struct SpriteVertex
{
	float x, y, z;
	float s, t;
	float padding[3];

	SpriteVertex(float p_x, float p_y, float p_z, float p_s, float p_t)
	{
		x = p_x;
		y = p_y;
		z = p_z;
		s = p_s;
		t = p_t;
	}
};


enum 
{
	GAME_OK, GAME_FAIL, GAME_OTHER
};

#endif