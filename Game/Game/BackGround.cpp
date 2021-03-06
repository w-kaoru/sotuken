#include "stdafx.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "TankInfo.h"
#include "StageData.h"

BackGround::BackGround()
{	
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	m_stageData = FindGO<StageData>("StageData");
	//cmoファイルの読み込み。
	m_model.Init(m_stageData->GetStageDeta()->filePath);
	m_staticObject.CreateMeshObject(
		m_model,
		m_stageData->GetStageDeta()->position,
		m_stageData->GetStageDeta()->rotation
	);
	m_model.SetShadowReciever(true);
	return true;
}

void BackGround::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(
		m_stageData->GetStageDeta()->position,
		m_stageData->GetStageDeta()->rotation,
		m_stageData->GetStageDeta()->scale
	);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
}

void BackGround::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void BackGround::Draw(int player_num)
{
	m_model.Draw(
		enRenderMode_Normal,
		g_gameCamera3D[player_num]->GetCamera().GetViewMatrix(),
		g_gameCamera3D[player_num]->GetCamera().GetProjectionMatrix()
	);
}