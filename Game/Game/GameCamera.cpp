#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Define.h"

GameCamera* g_gameCamera3D[PLAYER_NUM];  //ゲームカメラの配列。
//GameCamera* g_gameCamera2D[PLAYER_NUM];  //ゲームカメラの配列。
//カメラデータ。
struct SCameraData {
	float targetToPosition;		//注視点から視点までの距離。
	float cameraAngle;
	float upMax;
	float downMax;
};
GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_camera.SetFar(20000.0f);
	return true;
}

void GameCamera::Update()
{
	//ビューポート未設定なら終了。
	if (!m_isViewport)
	{
		return;
	}

	//現在の注視点から視点へのベクトルを求めるよ。
	CVector3 toCameraPos = m_camera.GetPosition() - m_camera.GetTarget();
	//新しい注視点を求める。
	CVector3 newTarget = m_target;

	float upMax = -40.0f;
	float downMax = 50.0f;

	//使用するカメラデータを決める。
	//カメラデータのテーブル。
	toCameraPos.Normalize();
	SCameraData cameraDataTbl[] = {
		{ 250.0f, CMath::DegToRad(60.0f), -25.0f, 20.0f},			//通常のカメラデータ。
		{ 1.0f, CMath::DegToRad(20.0f), -5.0f, 5.0f },			//ズームのカメラデータ。
	};
	if (m_aimFalg) {
		//ズームのカメラデータ。
		//使用するカメラデータを設定。
		toCameraPos *= cameraDataTbl[1].targetToPosition;
		m_camera.SetViewAngle(cameraDataTbl[1].cameraAngle);
		upMax = cameraDataTbl[1].upMax;
		downMax = cameraDataTbl[1].downMax;
		//Y方向にちょっと上げる。
		newTarget.y += 92.0f;
	}
	else
	{
		//通常のカメラデータ
		//使用するカメラデータを設定。
		toCameraPos *= cameraDataTbl[0].targetToPosition;
		m_camera.SetViewAngle(cameraDataTbl[0].cameraAngle);
		upMax = cameraDataTbl[0].upMax;
		downMax = cameraDataTbl[0].downMax;
		//Y方向にちょっと上げる。
		newTarget.y += 120.0f;
	}
	//パッドの入力を使ってカメラを回す。
	CVector3 RStick = CVector3::Zero();
	RStick.x = m_cameraSpeed * g_pad[m_number].GetRStickXF();
	RStick.y = m_cameraSpeed * g_pad[m_number].GetRStickYF();
	RStick.z = 0.0f;
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), RStick.x);
	qRot.Multiply(toCameraPos);
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), toCameraPos);
	axisX.Normalize();
	qRot.SetRotation(axisX, RStick.y);
	qRot.Multiply(toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	CVector3 toPosDir = toCameraPos;
	toPosDir.Normalize();
	float angle = toPosDir.Dot(m_camera.GetUp());
	angle = CMath::RadToDeg(angle);

	if (angle < upMax) {
		//カメラが上向きすぎ。
		angle -= upMax;
		qRot.SetRotationDeg(axisX, angle);
		qRot.Multiply(toCameraPos);
	}
	if (angle > downMax) {
		//	//カメラが下向きすぎ。
		angle -= downMax;
		qRot.SetRotationDeg(axisX, angle);
		qRot.Multiply(toCameraPos);
	}
	//新しい視点を計算する。
	auto newPos = newTarget + toCameraPos;
	m_camera.SetTarget(newTarget);
	m_camera.SetPosition(newPos);
	m_camera.Update();

}

