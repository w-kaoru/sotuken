/*!
 * @brief	定数バッファ
 */

#pragma once

#include "GPUBuffer.h"

namespace GameEngine {
	/*!
	 * @brief	定数バッファ。
	 */
	class ConstantBuffer : public GPUBuffer{
	public:
		ConstantBuffer();
		~ConstantBuffer();
		/*!
		*@brief ConstantBufferを作成。
		*@param[in]	pInitData		初期データ。
		*@param[in]	bufferSize		バッファサイズ。
		*/
		bool Create(const void* pInitData, int bufferSize );		
	};
}