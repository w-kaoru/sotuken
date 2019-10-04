/*!
 * @brief	StructuredBuffer
 */

#pragma once

#include "ShaderResourceView.h"
#include "UnorderedAccessView.h"
namespace GameEngine {
	/*!
	 * @brief	StructuredBuffer
	 */
	class StructuredBuffer : public NoncCopyable{
	public:
		StructuredBuffer();
		~StructuredBuffer();
		/*!
		* @brief	StructuredBuffer���쐬�B
		*@param[in]	pInitData		�����f�[�^�B
		*@param[in]	bufferDesc		�o�b�t�@��`�B
		*/
		bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
		/*!
		 * @brief	ID3D11Buffer*���擾�B
		 */
		ID3D11Buffer*& GetBody() 
		{
			return m_structuredBuffer;
		}
		/*!
		*@brief	�J���B
		*@details
		* ���̊֐��̓f�X�g���N�^������R�[������Ă��܂��B
		* �����I�ȃ^�C�~���O�ŊJ���������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release();
		/*!
		* @brief	SRV���擾�B
		*/
		ShaderResourceView& GetSRV()
		{
			return m_srv;
		}
		/*!
		* @brief	UAV���擾�B
		*/
		UnorderedAccessView& GetUAV()
		{
			return m_uav;
		}
	private:
		ID3D11Buffer*			m_structuredBuffer = nullptr;	//!<StructuredBuffer
		ShaderResourceView		m_srv;							//!<SRV
		UnorderedAccessView		m_uav;							//!<UAV
	};
}