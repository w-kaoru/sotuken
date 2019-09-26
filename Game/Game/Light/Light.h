#pragma once
#include "stdafx.h"

namespace GameEngine {
	/*!
	 *@brief	ディレクションライト。
	 */
	struct SDirectionLight
	{
		CVector4 color;			//!<ライトのカラー。
		CVector3 direction;		//!<ライトの方向。
	};
};