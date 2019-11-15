#include "stdafx.h"
#include "BoxCollider.h"


BoxCollider::~BoxCollider()
{
	delete m_shape;
}
