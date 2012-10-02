#ifndef SPRITEINFO_H
#define SPRITEINFO_H

#include <string>
#include "TransformInfo.h"

using namespace std;

struct SpriteInfo
{
public:
	int				id;
	string			textureFilePath;
	int				textureIndex;
	bool			visible;
	TransformInfo	transformInfo;

	SpriteInfo()
	{
		textureFilePath = "";
		textureIndex = -1;
		visible = true;
		transformInfo.rotation[0] = 0.0f;
		transformInfo.rotation[1] = 0.0f;
		transformInfo.rotation[2] = 0.0f;
		transformInfo.translation[0] = 0.0f;
		transformInfo.translation[1] = 0.0f;
		transformInfo.translation[2] = 0.0f;
		transformInfo.scale[0] = 0.0f;
		transformInfo.scale[1] = 0.0f;
		transformInfo.scale[2] = 0.0f;
	}

	SpriteInfo( string p_textureFilePath )
	{
		SpriteInfo();
		textureFilePath = p_textureFilePath;
	}

};

#endif