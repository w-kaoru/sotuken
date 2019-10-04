/*!
 * @brief	�萔�o�b�t�@
 */

#pragma once

#include "GPUBuffer.h"

namespace GameEngine {
	/*!
	 * @brief	�萔�o�b�t�@�B
	 */
	class ConstantBuffer : public GPUBuffer{
	public:
		ConstantBuffer();
		~ConstantBuffer();
		/*!
		*@brief ConstantBuffer���쐬�B
		*@param[in]	pInitData		�����f�[�^�B
		*@param[in]	bufferSize		�o�b�t�@�T�C�Y�B
		*/
		bool Create(const void* pInitData, int bufferSize );		
	};
}