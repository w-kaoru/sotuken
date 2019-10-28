#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Draw();
private:
	Sprite m_sprite;

};

