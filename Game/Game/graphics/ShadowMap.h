#pragma once
#include "RenderTarget.h"
class ShadowMap :public NoncCopyable
{
public:
	ShadowMap();
	~ShadowMap();
	//初期化。
	void Init();
	void UpdateToPosition(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	void UpdateToDirection(CVector3 lightCameraDir, CVector3 lightCameraTarget, float lightCameraLen = 50.0f);
	void RenderToShadowMap();
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点。
	CVector3 m_lightCameraTarget = CVector3::Zero();	//ライトカメラの注視点。
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//ライトビュー行列。
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//ライトプロジェクション行列。
	RenderTarget m_shadowMapRT;							//シャドウマップを描画するレンダリングターゲット。
	std::vector<SkinModel*> m_shadowCasters;			//シャドウキャスターの配列。
};