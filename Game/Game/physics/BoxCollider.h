#pragma once
#include "Physics/ICollider.h"

class BoxCollider : public ICollider
{
public:
	~BoxCollider();
	/*!
	* @brief	ì¬B
	*@param[in] halfLength	XYZ‚Ì”¼•ª‚Ì’·‚³B
	*/
	void Create(float halfLengthX, float halfLengthY, float halfLengthZ)
	{
		m_shape = new btBoxShape({ halfLengthX, halfLengthY, halfLengthZ });
		this->m_halfLengthX = halfLengthX;
		this->m_halfLengthY = halfLengthY;
		this->m_halfLengthZ = halfLengthZ;
	}
	btBoxShape* GetBody() const override
	{
		return m_shape;
	}
	float GetHalfLengthX() {
		return m_halfLengthX;
	}
	float GetHalfLengthY() {
		return m_halfLengthY;
	}
	float GetHalfLengthZ() {
		return m_halfLengthZ;
	}
private:
	btBoxShape*		m_shape;
	float m_halfLengthX = 0.0f;
	float m_halfLengthY = 0.0f;
	float m_halfLengthZ = 0.0f;

};