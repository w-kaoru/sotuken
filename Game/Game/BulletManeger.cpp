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

void BulletManeger::Update()
{
	for (auto& bullet : m_bulletList) {
		bullet->Update();
	}
}

void BulletManeger::Draw()
{
	for (auto& bullet : m_bulletList) {
		bullet->Draw();
	}
}