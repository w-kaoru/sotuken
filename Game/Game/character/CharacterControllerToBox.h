/*!
* @brief	キャラクタコントローラー。
*/

#pragma once

#include "Physics/RigidBody.h"
#include "physics/BoxCollider.h"

/*!
* @brief	キャラクタコントローラー。
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
		* @brief	初期化。
		*@param[in]	halfLength	BOXコライダーの半分の長さ。
		*@param[in]	position	初期位置。
		*/
	void Init(CVector3 halfLength, const CVector3& position);
	/*!
		* @brief	実行。
		*@param[in]	deltaTime		経過時間。単位は秒。
		*@param[in, out]	moveSpeed		移動速度。内部で重力加速が計算され、その結果がmoveSpeedに反映されます。
		*@return 移動後のキャラクターの座標。
		*/
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed, CQuaternion rot);
	/*!
		* @brief	座標を取得。
		*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	座標を設定。
		*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/*!
		* @brief	ジャンプ中か判定
		*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	地面上にいるか判定。
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	コライダーを取得。
	*/
	BoxCollider* GetCollider()
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
	/*!
	* @brief	剛体を物理エンジンから削除。。
	*/
	void RemoveRigidBoby();

	void SetPlayerNumber(int num) {
		m_playerNumber = num;
	}
	int GetPlayerNumber() {
		return m_playerNumber;
	}
private:
	CVector3 			m_position = CVector3::Zero();	//座標。
	bool 				m_isJump = false;				//ジャンプ中？
	bool				m_isOnGround = true;			//地面の上にいる？
	BoxCollider			m_collider;						//コライダー。
	CVector3			m_halfLength;
	RigidBody			m_rigidBody;					//剛体。
	btQuaternion		m_fRot = { 0.0f,0.0f,0.0f,1.0f };
	int					m_playerNumber = 0;				//プレイヤーの番号
};
