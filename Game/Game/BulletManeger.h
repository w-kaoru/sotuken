#pragma once
#include "Bullet.h"
class BulletManeger : public IGameObject
{
public:
	BulletManeger();
	~BulletManeger();
	bool Start();
	Bullet* NewBullet();
	void Update();
	void Draw();
private:
	std::vector<Bullet*> m_bulletList;
	int i = 0;
};

