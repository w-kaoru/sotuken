#pragma once
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void Draw();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetMoveSpeed(CVector3 speed)
	{
		m_moveSpeed += speed;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
};

