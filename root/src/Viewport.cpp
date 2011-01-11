#include "Viewport.h"

Viewport::Viewport(const int width, const int height)
{
	m_BotLY = height;
	m_BotLX = 0;
	m_TopRY = 0;
	m_TopRX = width;
}

void Viewport::UpdateViewport(const int width, const int height)
{
	m_BotLY = height;
	m_BotLX = 0;
	m_TopRY = 0;
	m_TopRX = width;
}
