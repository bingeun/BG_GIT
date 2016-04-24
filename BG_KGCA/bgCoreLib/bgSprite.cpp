#include "bgSprite.h"



bool bgSprite::Init()
{
	m_iterFrame = m_Frame.begin();
	return true;
}

bool bgSprite::Frame()
{
	return true;
}

bool bgSprite::Render()
{
	return true;
}

bool bgSprite::Release()
{
	return true;
}

bgSprite::bgSprite()
{
}


bgSprite::~bgSprite()
{
}
