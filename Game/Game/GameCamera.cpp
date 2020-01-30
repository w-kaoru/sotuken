#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Define.h"

//�J�����f�[�^�B
struct SCameraData {
	float targetToPosition;		//�����_���王�_�܂ł̋����B
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
	g_camera3D.SetPosition(m_position);
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetFar(20000.0f);
	return true;
}

void GameCamera::Update()
{
	//���݂̒����_���王�_�ւ̃x�N�g�������߂��B
	CVector3 toCameraPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
	//�V���������_�����߂�B
	CVector3 newTarget = m_target;

	float upMax = -40.0f;
	float downMax = 50.0f;

	//�g�p����J�����f�[�^�����߂�B
	//�J�����f�[�^�̃e�[�u���B
	toCameraPos.Normalize();
	SCameraData cameraDataTbl[] = {
		{ 250.0f, CMath::DegToRad(60.0f), -25.0f, 20.0f},			//�ʏ�̃J�����f�[�^�B
		{ 1.0f, CMath::DegToRad(20.0f), -5.0f, 5.0f },			//�Y�[���̃J�����f�[�^�B
	};
	if (m_aimFalg) {
		//�Y�[���̃J�����f�[�^�B
		//�g�p����J�����f�[�^��ݒ�B
		toCameraPos *= cameraDataTbl[1].targetToPosition;
		g_camera3D.SetViewAngle(cameraDataTbl[1].cameraAngle);
		upMax = cameraDataTbl[1].upMax;
		downMax = cameraDataTbl[1].downMax;
		//Y�����ɂ�����Əグ��B
		newTarget.y += 92.0f;
	}
	else
	{
		//�ʏ�̃J�����f�[�^
		//�g�p����J�����f�[�^��ݒ�B
		toCameraPos *= cameraDataTbl[0].targetToPosition;
		g_camera3D.SetViewAngle(cameraDataTbl[0].cameraAngle);
		upMax = cameraDataTbl[0].upMax;
		downMax = cameraDataTbl[0].downMax;
		//Y�����ɂ�����Əグ��B
		newTarget.y += 120.0f;
	}
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	CVector3 RStick = CVector3::Zero();
	RStick.x = m_cameraSpeed * g_pad[0].GetRStickXF();
	RStick.y = m_cameraSpeed * g_pad[0].GetRStickYF();
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

