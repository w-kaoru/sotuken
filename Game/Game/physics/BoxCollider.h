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
	void Create(CVector3 halfLength)
	{
		m_shape = new btBoxShape(btVector3(halfLength.x, halfLength.y, halfLength.z));
		this->m_halfLengthCV = halfLength;
		this->m_halfLengthBV = btVector3(halfLength.x, halfLength.y, halfLength.z);
	}
	btBoxShape* GetBody() const override
	{
		return m_shape;
	}
	btVector3 GetHalfLengthBV() 
	{
		return m_halfLengthBV;
	}
	CVector3 GetHalfLengthCV()
	{
		return m_halfLengthCV;
	}
private:
	btBoxShape*		m_shape = nullptr;
	btVector3 m_halfLengthBV = btVector3(0.0f, 0.0f, 0.0f);
	CVector3 m_halfLengthCV = CVector3::Zero();
};