#pragma once
#include "Sprite.h"
#include "../Light/LightManager.h"
#include "ShadowMap.h"
// レンダリングモード。
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Num,				//レンダリングモードの数。
};
/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// ゲームでデフォルトのフォントを取得
	/// </summary>
	/// <returns>
	/// フォントデータ（DirectX::SpriteFont*）
	/// </returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_SpriteFont;
	}
	/// <summary>
	/// フォント表示に必要なクラスを取得
	/// </summary>
	/// <returns>
	/// フォント表示に必要なクラス（DirectX::SpriteBatch*）
	/// </returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_SpriteBatch;
	}
	/// <summary>
	/// ラスタライザステートのゲット
	/// </summary>
	/// <returns>
	/// ラスタライザステート（ID3D11RasterizerState* ）
	/// </returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}
	/*!
	*@brief	ライトの管理者を取得。
	*/
	GameEngine::LightManager* GetLightManager()
	{
		return &m_ligManager;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
	/// <summary>
	/// エフェクトのマネージャークラスの取得
	/// </summary>
	/// <returns>
	/// エフェクトのマネージャークラス（Effekseer::Manager*）
	/// </returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_effekseerManager;
	}
	void EffectUpdate()
	{
		//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//カメラ行列とプロジェクション行列を設定。
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseerを更新。
		m_effekseerManager->Update();
		EffectDraw();
	}
	void EffectDraw()
	{
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
	}
	// シャドウマップクラスの取得
	ShadowMap* GetShadowMap() {
		return &m_shadowMap;
	}
	/// <summary>
	/// レンダリングターゲットの切り替え。
	/// </summary>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	void PreRender();
	void PostRender();
	/// <summary>
	/// メインレンダリングターゲットを取得。
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	Sprite* GetSprite()
	{
		return &m_sprite;
	}
private:
	GameEngine::LightManager	m_ligManager;
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	DirectX::SpriteFont*    m_SpriteFont = NULL;		//ゲームのデフォルトのフォントデータ
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;		//ゲームのデフォルトのフォント表示用データ
	Effekseer::Manager*	m_effekseerManager = nullptr;	//エフェクトマネージャークラス
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;  //エフェクトレンダラークラス
	ShadowMap				m_shadowMap;					//シャドウマップ。
	RenderTarget			m_mainRenderTarget;				//メインレンダリングターゲット。
	Sprite					m_sprite;//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。

	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン
