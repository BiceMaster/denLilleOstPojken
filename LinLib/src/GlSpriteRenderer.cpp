#include "GlSpriteRenderer.h"

#ifndef _WIN32
#define FALSE 0
#define TRUE 1
#endif

GlSpriteRenderer::GlSpriteRenderer(GlContext* p_context)
{
	DEBUGPRINT(("Creating sprite renderer...\n"));
	m_initialized	= false;
	m_context		= p_context;
	m_spriteShader	= new GlSpriteShader();
	if (!m_spriteShader->isInitialized())
		return;
	if (initializeGeometry() != GAME_OK)
		return;
	GLErrCheck();
	
	m_positionX = 0;
	m_positionY = 0;
//	load("../Textures/LogoGL.png");
	m_initialized = true;
}
GlSpriteRenderer::~GlSpriteRenderer()
{
	delete m_spriteShader;
}
int GlSpriteRenderer::initializeGeometry()
{
	SpriteVertex vertices[] =
	{  
		SpriteVertex(-1.0f,  1.0f, 0.0f, 0.0f, 0.0f),  
		SpriteVertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f),
		SpriteVertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f),
		SpriteVertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f),
		SpriteVertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		SpriteVertex(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f)
	};

	//Create a buffer and add the vertices to it.
	//Buffer must be bound when the vertices are added.
	glGenBuffers(1,&m_vertexBuffer); GLErrCheck();
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); GLErrCheck();
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteVertex)*6, 
		vertices, GL_STATIC_DRAW); GLErrCheck();

	//Map the CPU data to the shader data for the input assembler.
	glVertexAttribPointer (m_spriteShader->getPostionIndex(), 3, GL_FLOAT, 
		GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex,x)); GLErrCheck();
	glVertexAttribPointer (m_spriteShader->getTexCoordIndex(), 2, GL_FLOAT, 
		GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex,s)); GLErrCheck();
	return 0;
}
void GlSpriteRenderer::setPosition(float p_positionX, float p_positionY)
{
	m_positionX = p_positionX;
	m_positionY = p_positionY;
}
int GlSpriteRenderer::draw()
{
	glUseProgram(m_spriteShader->getID()); GLErrCheck();
	 
	glUniform4f(m_spriteShader->getCenterPositionConstant(), 
		m_spriteInfo->transformInfo.translation[TransformInfo::X],
		m_spriteInfo->transformInfo.translation[TransformInfo::Y],
		m_spriteInfo->transformInfo.translation[TransformInfo::Z],
		0.0f
	); GLErrCheck();

	glActiveTexture(GL_TEXTURE0);
	// :NOTE: Must bind texture before retrieving width and height
	glBindTexture(GL_TEXTURE_2D, m_texture); GLErrCheck();

	int textureWidth, textureHeight;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth); GLErrCheck();
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight); GLErrCheck();

	if (m_spriteInfo->textureIndex == 3)
	{
		int i = 0;
	}

	glUniform4f(m_spriteShader->getTextureRectConstant(),
		(float)m_spriteInfo->textureRect.x / textureWidth,
		(float)m_spriteInfo->textureRect.y / textureHeight,
		(float)m_spriteInfo->textureRect.width / textureWidth,
		(float)m_spriteInfo->textureRect.height / textureHeight
	); GLErrCheck();
	glUniform2f(m_spriteShader->getHalfScaleConstant(),
		m_spriteInfo->transformInfo.scale[TransformInfo::X] / 2,
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] / 2
	); GLErrCheck();
	glUniform2f(m_spriteShader->getScreenSizeConstant(), 
		(GLfloat)m_context->getScreenWidth(), (GLfloat)m_context->getScreenHeight()
	); GLErrCheck();

	glEnableVertexAttribArray(m_spriteShader->getPostionIndex()); GLErrCheck();
	glEnableVertexAttribArray(m_spriteShader->getTexCoordIndex()); GLErrCheck();
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); GLErrCheck();
	glDrawArrays(GL_TRIANGLES, 0, 6); GLErrCheck();
	glDisableVertexAttribArray(m_spriteShader->getPostionIndex()); GLErrCheck();
	glDisableVertexAttribArray(m_spriteShader->getTexCoordIndex()); GLErrCheck();
	return 0;
}

/*
GLboolean GlSpriteRenderer::load(string path)
{
	vector<unsigned char> rawImage;
	lodepng::State state;

	lodepng::load_file(rawImage, path);
	std::vector<unsigned char> image;

	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, state, rawImage);

	if (error)
	{
		const char* err = lodepng_error_text(error);
		return FALSE;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
		GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//free(data);
	return TRUE;
}
*/

bool GlSpriteRenderer::isInitialized()
{
	return m_initialized;
}

void GlSpriteRenderer::setSpriteInfo( SpriteInfo* p_spriteInfo )
{
	m_spriteInfo = p_spriteInfo;
}

void GlSpriteRenderer::setTexture(GLuint p_texture)
{
	m_texture = p_texture;
}
