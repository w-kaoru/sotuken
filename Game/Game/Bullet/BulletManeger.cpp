#include "stdafx.h"
#include "BulletManeger.h"


BulletManeger::BulletManeger()
{
}


BulletManeger::~BulletManeger()
{
}

bool BulletManeger::Start()
{
	return true;
}
Bullet* BulletManeger::NewBullet()
{
	Bullet* newbullet = NewGO<Bullet>(1, "Bullet");
	m_bulletList.push_back(newbullet);
	return newbullet;
}
void BulletManeger::DeleteBullet()
{
	m_bulletDeleteTime++;
	for (auto& bullet : m_bulletList) {
		if (m_bulletDeleteTime > 75 
			||bullet->GetEHit() == true 
			||bullet->GetPHit() == true)
		{
				DeleteGO(bullet);
				m_bulletDeleteTime = 0;
				m_bulletList.erase(std::remove(m_bulletList.begin(), m_bulletList.end(), bullet)
					, m_bulletList.end());
		}
		if (bullet->GetEHit() == true)
		{
			kariflag = true;
		}
	}
}
void BulletManeger::Update()
{

	for (auto& bullet : m_bulletList) {
		//bullet->BulletMove();
	}
	DeleteBullet();
}

void BulletManeger::Draw()
{
	/*for (auto& bullet : m_bulletList) {
		bullet->Draw();
	}*/
}