#include "stdafx.h"
#include "SphereCollider.h"


/*!
* @brief	コンストラクタ。
*/
SphereCollider::SphereCollider() :
	shape(nullptr)
{
}

/*!
* @brief	デストラクタ。
*/
SphereCollider::~SphereCollider()
{
	delete shape;
}
