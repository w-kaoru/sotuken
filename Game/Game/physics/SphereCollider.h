#pragma once
#include "Physics/ICollider.h"
class SphereCollider : public ICollider
{
public:
	SphereCollider();
	~SphereCollider();
	/*!
	* @brief	�쐬�B
	*@param[in] radius	���̂̔��a�B
	*/
	void Create(float radius)
	{
		shape = new btSphereShape(radius);//, height);
		this->radius = radius;
	}
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
	float GetRadius() const
	{
		return radius;
	}
private:
	btSphereShape * shape = nullptr;
	float radius = 0.0f; //���a�B
};

