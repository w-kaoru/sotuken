#pragma once
#include "stdafx.h"

namespace GameEngine {
	struct SLightParam {
		CVector3 eyePos;			//�����̈ʒu�B
		int numDirectionLight;		//�f�B���N�V�������C�g�̐��B
	};
	/*!
	 *@brief	�f�B���N�V�������C�g�B
	 */
	struct SDirectionLight
	{
		CVector4 color;			//!<���C�g�̃J���[�B
		CVector3 direction;		//!<���C�g�̕����B
	};
};