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
		//���݂̒����_���王�_�ւ̃x�N�g�������߂��B
		CVector3 toCameraPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
		//�V���������_�����߂�B
		CVector3 newTarget = m_player->GetPosition();
		//Y�����ɂ�����Əグ��B
		newTarget.y += 120.0f;
		//�V�������_���v�Z����B

		//�p�b�h�̓��͂��g���ăJ�������񂷁B
		CVector3 RStick = CVector3::Zero();
		RStick.x = 0.05f * g_pad[0].GetRStickXF();
		RStick.y = 0.05f * g_pad[0].GetRStickYF();
		RStick.z = 0.0f;
		//Y������̉�]
		CQuaternion qRot;
		qRot.SetRotation(CVector3::AxisY(), RStick.x);
		qRot.Multiply(toCameraPos);
		//X������̉�]�B
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), toCameraPos);
		axisX.Normalize();
		qRot.SetRotation(axisX, RStick.y);
		qRot.Multiply(toCameraPos);
		//�J�����̉�]�̏�����`�F�b�N����B
		//�����_���王�_�܂ł̃x�N�g���𐳋K������B
		//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
		//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
		CVector3 toPosDir = toCameraPos;
		toPosDir.Normalize();
		float angle = toPosDir.Dot(g_camera3D.GetUp());
		angle = CMath::RadToDeg(angle);
		float upMax = -40.0f;
		float downMax = 50.0f;
		if (angle < upMax) {
			//�J����������������B
			angle -= upMax;
			qRot.SetRotationDeg(axisX, angle);
			qRot.Multiply(toCameraPos);
		}
		if (angle > downMax) {
			//	//�J�����������������B
			angle -= downMax;
			qRot.SetRotationDeg(axisX, angle);
			qRot.Multiply(toCameraPos);

		}
		//�V�������_���v�Z����B
		auto newPositin = newTarget + toCameraPos;
		g_camera3D.SetTarget(newTarget);
		g_camera3D.SetPosition(newPositin);
		g_camera3D.Update();

	}
}