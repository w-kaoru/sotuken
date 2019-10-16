#pragma once
#include "Physics/ICollider.h"
class SphereCollider : public ICollider
{
public:
	SphereCollider();
	~SphereCollider();
	/*!
	* @brief	ì¬B
	*@param[in] radius	‹…‘Ì‚Ì”¼ŒaB
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
	float radius = 0.0f; //”¼ŒaB
};

