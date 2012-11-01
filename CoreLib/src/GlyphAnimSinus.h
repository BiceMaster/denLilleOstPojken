#ifndef GLYPHANIMSINUS_H
#define GLYPHANIMSINUS_H

#include <cmath>
#include "GlyphAnimation.h"

class GlyphAnimSinus : public GlyphAnimation
{
private:
	float m_totTime;
public:
	GlyphAnimSinus();
	void update( float p_dt );
	TransformInfo getAnimation( TransformInfo p_transInfo,
		float p_freq, float p_amplitude, float p_speed );
	virtual void reset();
};
#endif // GLYPHANIMSINUS_H