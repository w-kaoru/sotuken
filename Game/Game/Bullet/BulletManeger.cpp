#include "stdafx.h"
#include "BulletManeger.h"
#include "Physics/CollisionAttr.h"



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
void BulletManeger::OnDestroy()
{
	for (auto& bullet : m_bulletList)
	{
		DeleteGO(bullet);
	}

}
Bullet* BulletManeger::NewBullet(int k,int number)
{
	Bullet* newbullet = NewGO<Bullet>(1, "Bullet");
	newbullet->Init(k, number);
	m_bulletList.push_back(newbullet);
	return newbullet;
}
void BulletManeger::DeleteBullet()
{
	
	for (auto& bullet : m_bulletList) {

		if (bullet->GetBulletHit() == true)
		{
			m_damage = true;
			m_number = bullet->GetNumber();
		}
		if (bullet->GetTime() > 75
			|| bullet->GetBulletHit() == true
			|| bullet->GetHit() == true)
		{
			DeleteGO(bullet);
			m_bulletList.erase(std::remove(m_bulletList.begin(), m_bulletList.end(), bullet)
				, m_bulletList.end());
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