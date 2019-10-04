/*!
 * @brief	�萔�o�b�t�@�B
 */

#include "stdafx.h"
#include "ConstantBuffer.h"


namespace GameEngine {
	ConstantBuffer::ConstantBuffer()
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	/*!
	*@brief ConstantBuffer���쐬�B
	*@param[in]	pInitData		�����f�[�^�B
	*@param[in]	bufferSize		�o�b�t�@�T�C�Y�B
	*/
	bool ConstantBuffer::Create(const void* pInitData, int bufferSize)
	{
		//ConstantBuffer�p�̃o�b�t�@��`���쐬����B
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = (((bufferSize-1)/16)+1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		return GPUBuffer::Create(pInitData, bufferDesc);
	}
}