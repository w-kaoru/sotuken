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

	m_explosionse.Init(L"Assets/sound/explosion.wav");
	m_explosionse.SetVolume(0.5f);
	m_attsckse.Init(L"Assets/sound/battery1.wav");
	m_testEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/exproj.efk");
	return true;
}
void BulletManeger::OnDestroy()
{
	for (auto& bullet : m_bulletList)
	{
		DeleteGO(bullet);
	}

}
Bullet* BulletManeger::NewBullet(int collision,int number)
{
	Bullet* newbullet = NewGO<Bullet>(1, "Bullet");
	m_attsckse.Play(false);
	newbullet->Init(collision, number);
	m_bulletList.push_back(newbullet);
	return newbullet;
}
void BulletManeger::DeleteBullet(Bullet* bullet)
{
	if (bullet->GetBulletHit() == true)
	{
		m_damage = true;
		m_number = bullet->GetNumber();
		m_hitNumber = bullet->GetHitNumber();
	}
	if (bullet->GetTime() > 75
		|| bullet->GetBulletHit() == true
		|| bullet->GetHit() == true)
	{
		DeleteGO(bullet);
		m_bulletList.erase(
			std::remove(m_bulletList.begin(), m_bulletList.end(), bullet),
			m_bulletList.end()
		);
	}
}

void BulletManeger::Update()
{

	for (auto& bullet : m_bulletList) {
		//bullet->BulletMove();
		//DeleteBullet(bullet);
		if (bullet->GetBulletHit() == true)
		{
			m_damage = true;
			m_number = bullet->GetNumber();
			m_hitNumber = bullet->GetHitNumber();
		}
		if (bullet->GetTime() > 75
			|| bullet->GetBulletHit() == true
			|| bullet->GetHit() == true)
		{
			m_explosionse.Play(false);
			m_testEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(
				m_testEffect, bullet->GetPosition().x, bullet->GetPosition().y, bullet->GetPosition().z);
			DeleteGO(bullet);
			bullet = nullptr;
		}
	}

	for (auto& bullet : m_bulletList) {
		if (!bullet) {
			m_bulletList.erase(
				std::remove(m_bulletList.begin(), m_bulletList.end(), bullet),
				m_bulletList.end()
			);
		}
	}
}

void BulletManeger::Draw()
{
	/*for (auto& bullet : m_bulletList) {
		bullet->Draw();
	}*/
}