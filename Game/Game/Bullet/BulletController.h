#pragma once
#include "physics/SphereCollider.h"
#include "physics/RigidBody.h"
namespace GameEngine {
	class BulletController
	{
	public:
		BulletController();
		~BulletController();
		virtual void Init(float radius, const CVector3& position);
		virtual const CVector3& Execute(float deltaTime, CVector3& moveSpeed);
		const CVector3& GetPotion() const
		{
			return m_position;
		}
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/*!
		* @brief	�R���C�_�[���擾�B
		*/
		SphereCollider* GetCollider()
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
		void RemoveRigidBoby();

		bool Gethit()
		{
			return hitFlag;
		}
		bool GetE_bullethit()
		{
			return E_bullethitFlag;
		}
	private:
		CVector3 m_position = CVector3::Zero();
		SphereCollider m_collider;
		RigidBody m_rigidBody;
		float m_radius = 0.0f;
		float m_height = 0.0f;
		bool hitFlag = false;
		bool E_bullethitFlag = false;   //�G�e���v���C���[�ɂԂ��������Ƃ�m�点��t���O�B
		bool deathflag = true;   //�e�����݂��Ă��邩�𔻒肷��B
	};
};
