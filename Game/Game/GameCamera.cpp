#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Define.h"

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

	//m_player = FindGO<Player>("Player");
	g_camera3D.SetPosition(
		{ m_player->GetPosition().x,m_player->GetPosition().y + 130.0f,
		m_player->GetPosition().z + 250.0f
		}
	);
	g_camera3D.SetTarget(m_player->GetPosition());
	g_camera3D.SetFar(20000.0f);
	return true;
}

void GameCamera::Update()
{
	if (m_player != nullptr) {
		//現在の注視点から視点へのベクトルを求めるよ。
		CVector3 toCameraPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
		//新しい注視点を求める。
		CVector3 newTarget = m_player->GetPosition(); 

		float upMax = -40.0f;
		float downMax = 50.0f;

		//使用するカメラデータを決める。
		//カメラデータのテーブル。
		toCameraPos.Normalize();
		SCameraData cameraDataTbl[] = {
			{ 250.0f, CMath::DegToRad(60.0f), -25.0f, 20.0f},			//通常のカメラデータ。
			{ 1.0f, CMath::DegToRad(20.0f), - 5.0f, 5.0f },			//ズームのカメラデータ。
		};
		if (g_pad[0].IsPress(enButtonLB2)) {
			//使用するカメラデータを設定。
			toCameraPos *= cameraDataTbl[1].targetToPosition;
			g_camera3D.SetViewAngle(cameraDataTbl[1].cameraAngle);
			upMax = cameraDataTbl[1].upMax;
			downMax = cameraDataTbl[1].downMax;
			//Y方向にちょっと上げる。
			newTarget.y += 92.0f;
		}
		else
		{
			//使用するカメラデータを設定。
			toCameraPos *= cameraDataTbl[0].targetToPosition;
			g_camera3D.SetViewAngle(cameraDataTbl[0].cameraAngle);
			upMax = cameraDataTbl[0].upMax;
			downMax = cameraDataTbl[0].downMax;
			//Y方向にちょっと上げる。
			newTarget.y += 120.0f;
		}
		//パッドの入力を使ってカメラを回す。
		CVector3 RStick = CVector3::Zero();
		RStick.x = m_player->GetCameraSpeed() * g_pad[0].GetRStickXF();
		RStick.y = m_player->GetCameraSpeed() * g_pad[0].GetRStickYF();
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
		float angle = toPosDir.Dot(g_camera3D.GetUp());
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
		auto newPositin = newTarget + toCameraPos;
		g_camera3D.SetTarget(newTarget);
		g_camera3D.SetPosition(newPositin);
		g_camera3D.Update();

	}
}