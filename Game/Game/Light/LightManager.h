#pragma once
#include "LightBase.h"
#include "Light.h"

namespace GameEngine {
	namespace prefab {
		class DirectionLight;
		class LightBase;
	}
	class LightManager
	{
	public:
		LightManager();
		~LightManager();
		void Init();
		void AddLight(prefab::LightBase* lig);
		void RemoveLight(prefab::LightBase* lig);
		void InitDirectionLightStructuredBuffer();
		void InitDirectionLightShaderResourceView();
		void InitLightParamConstantBuffer();
		//更新。
		void Update();
		//描画シーケンスから呼ばれる処理。
		void Render();
		void SetLightParam(CVector3 eyePos,int directionLightNum)
		{
			m_lightParam.eyePos = eyePos;
			m_lightParam.numDirectionLight = directionLightNum;
		}
		void SetEyePos(CVector3 pos) 
		{
			m_lightParam.eyePos = pos;
		}
	private:
		static const int MAX_DIRECTION_LIGHT = 4;						//!<ディレクションライトの最大数。
		/*!
		 *@brief	GPUで使用するライト用のパラメータ。
		 *@details
		 * メンバ変数を追加したり、並びを変えたりしたら
		 * Assets/shader/modelCB.hのlightCbも変える必要あり。
		 */
		SLightParam							m_lightParam;
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];
		std::list<prefab::DirectionLight*>	m_directionLights;		//!<平行光源のリスト。
		//ConstantBuffer						m_lightParamCB;
		//StructuredBuffer					m_directionLightSB;
		ID3D11Buffer*						m_lightParamCB = nullptr;		//!<コンスタントバッファ。
		ID3D11Buffer*						m_directionLightSB = nullptr;	//!<ストラクチャーバッファ。
		ID3D11ShaderResourceView*			m_directionLightSRV = nullptr;	//!<SRV。
	};
}
