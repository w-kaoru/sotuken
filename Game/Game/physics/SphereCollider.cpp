#include "stdafx.h"
#include "SphereCollider.h"


/*!
* @brief	�R���X�g���N�^�B
*/
SphereCollider::SphereCollider() :
	shape(nullptr)
{
}

/*!
* @brief	�f�X�g���N�^�B
*/
SphereCollider::~SphereCollider()
{
	delete shape;
}
