#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{

	m_player = FindGO<Player>("Player");
	g_camera3D.SetPosition(
		{ 0.0f,m_player->GetPosition().y + 130.0f,
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
		//Y方向にちょっと上げる。
		newTarget.y += 120.0f;
		//新しい視点を計算する。

		//パッドの入力を使ってカメラを回す。
		CVector3 RStick = CVector3::Zero();
		RStick.x = 0.05f * g_pad[0].GetRStickXF();
		RStick.y = 0.05f * g_pad[0].GetRStickYF();
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
		float upMax = -40.0f;
		float downMax = 50.0f;
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