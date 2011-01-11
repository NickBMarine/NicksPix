class Viewport
{
public:
	int m_TopRX, 
		m_TopRY,
		m_BotLX,
		m_BotLY;

	Viewport() {};
	Viewport(const int width, const int height);
	void UpdateViewport(const int width, const int height);
	int TopRX() { return m_TopRX;};
	int TopRY() { return m_TopRY;};
	int BotLX() { return m_BotLX;};
	int BotLY() { return m_BotLY;};
};
