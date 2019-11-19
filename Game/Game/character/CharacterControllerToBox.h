/*!
* @brief	�L�����N�^�R���g���[���[�B
*/

#pragma once

#include "Physics/RigidBody.h"
#include "physics/BoxCollider.h"

/*!
* @brief	�L�����N�^�R���g���[���[�B
*/
class CharacterControllerToBox{
public:
	CharacterControllerToBox() {

	}
	~CharacterControllerToBox()
	{
		RemoveRigidBoby();
	}
	/*!
		* @brief	�������B
		*@param[in]	radius		�J�v�Z���R���C�_�[�̔��a�B
		*@param[in]	height		�J�v�Z���R���C�_�[�̍����B
		*@param[in]	position	�����ʒu�B
		*/
	void Init(CVector3 halfLength, const CVector3& position);
	/*!
		* @brief	���s�B
		*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
		*@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
		*@return �ړ���̃L�����N�^�[�̍��W�B
		*/
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed, CQuaternion rot);
	/*!
		* @brief	���W���擾�B
		*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	���W��ݒ�B
		*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/*!
		* @brief	�W�����v��������
		*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	�n�ʏ�ɂ��邩����B
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	BoxCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	���̂��擾�B
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
private:
	CVector3 			m_position = CVector3::Zero();	//���W�B
	bool 				m_isJump = false;				//�W�����v���H
	bool				m_isOnGround = true;			//�n�ʂ̏�ɂ���H
	BoxCollider			m_collider;						//�R���C�_�[�B
	CVector3			m_halfLength;
	RigidBody			m_rigidBody;					//���́B
	btQuaternion		m_fRot = { 0.0f,0.0f,0.0f,1.0f };
};
