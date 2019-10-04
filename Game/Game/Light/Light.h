#pragma once
#include "stdafx.h"

namespace GameEngine {
	struct SLightParam {
		CVector3 eyePos;			//視線の位置。
		int numDirectionLight;		//ディレクションライトの数。
	};
	/*!
	 *@brief	ディレクションライト。
	 */
	struct SDirectionLight
	{
		CVector4 color;			//!<ライトのカラー。
		CVector3 direction;		//!<ライトの方向。
	};
};