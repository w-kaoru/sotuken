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
		* @brief	コライダーを取得。
		*/
		SphereCollider* GetCollider()
		{
			return &m_collider;
		}
		/*!
		* @brief	剛体を取得。
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
		bool E_bullethitFlag = false;   //敵弾がプレイヤーにぶつかったことを知らせるフラグ。
		bool deathflag = true;   //弾が存在しているかを判定する。
	};
};
