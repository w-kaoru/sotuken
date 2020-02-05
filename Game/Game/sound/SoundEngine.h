

#pragma once
#include "sound/WaveFileBank.h"

#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//最大出力チャンネル数。

/// <summary>
/// サウンドエンジン。
/// </summary>
namespace GameEngine {
	class CWaveFile;
	namespace prefab {
		class CSoundSource;
	}
	class CSoundEngine {
	public:
		/// <summary>
		/// コンストラクタ。
		/// </summary>
		CSoundEngine();
		/// <summary>
		/// デストラクタ。
		/// </summary>
		~CSoundEngine();

		/// <summary>
		/// 初期化。
		/// </summary>
		void Init();
		/// <summary>
		/// 解放
		/// </summary>
		/// <remarks>
		/// デストラクタから呼ばれています。
		/// 明示的に開放したい場合に使用してください。
		/// </remarks>
		void Release();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		/*!
			* @brief	3Dサウンドソースを追加。
			*/
		void Add3DSoundSource(prefab::CSoundSource* s)
		{
			m_soundSources.push_back(s);
		}
		/*!
		* @brief	3Dサウンドソースを削除。
		*/
		void Remove3DSoundSource(prefab::CSoundSource* s)
		{
			auto it = std::find(m_soundSources.begin(), m_soundSources.end(), s);
			if (it != m_soundSources.end()) {
				m_soundSources.erase(it);
			}
		}
		/*!
		* @brief	サウンドリスナーの座標を設定。
		* @details
		*  3D音源を使っている時の計算に使用されます。
		*/
		void SetListenerPosition(const CVector3& pos)
		{
			m_listenerPosition = pos;
		}
		/*!
		* @brief	サウンドリスナーの前方向を設定。
		* @details
		*  3D音源を使っている時の計算に使用されます。
		*/
		void SetListenerFront(CVector3 front)
		{
			m_listener.OrientFront.x = front.x;
			m_listener.OrientFront.y = front.y;
			m_listener.OrientFront.z = front.z;
		}
		/*!
		* @brief	サウンドリスナーの上方向を設定。
		* @details
		*  3D音源を使っている時の計算に使用されます。
		*/
		void SetListenerUp(CVector3 up)
		{
			m_listener.OrientTop.x = up.x;
			m_listener.OrientTop.y = up.y;
			m_listener.OrientTop.z = up.z;
		}
		/// <summary>
		/// XAudio2のソースボイスの作成。
		/// </summary>
		/// <param name="waveFile"></param>
		/// <param name="is3DSound"></param>
		/// <returns></returns>
		IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile, bool is3DSound);
		IXAudio2MasteringVoice* GetMasteringVoice()
		{
			return m_masteringVoice;
		}
		IXAudio2SubmixVoice* GetSubmixVoice()
		{
			return m_submixVoice;
		}

		/// <summary>
		/// 出力チャンネルの数を取得。
		/// </summary>
		/// <returns></returns>
		int GetNumChannel() const
		{
			return m_nChannels;
		}

		/// <summary>
		/// 波形データバンクを取得。
		/// </summary>
		CWaveFileBank& GetWaveFileBank()
		{
			return m_waveFileBank;
		}

		/*!
		 *@brief	インスタンスの取得。
		 */
		static CSoundEngine& Instance()
		{
			static CSoundEngine instance;
			return instance;
		}
	private:
		IXAudio2* m_xAudio2 = nullptr;
		IXAudio2MasteringVoice* m_masteringVoice = nullptr;
		X3DAUDIO_HANDLE m_hx3DAudio;					//!<3Dオーディオのハンドル。
		IUnknown* m_reverbEffect = nullptr;				//!<リバープエフェクト。
		IXAudio2SubmixVoice* m_submixVoice = nullptr;	//!<サブミックスボイス。
		DWORD m_channelMask = 0;						//!<オーディオチャンネルマスク。
		DWORD m_nChannels = 0;							//!<チャンネル数。
		CVector3 m_listenerPosition = CVector3::Zero();
		float m_fListenerAngle = 0.0f;
		bool m_UseListenerCone = false;
		bool m_fUseInnerRadius = false;
		bool m_useRedirectToLFE = false;
		bool m_isInited = false;
		X3DAUDIO_LISTENER m_listener;					//!<サウンドリスナー。
		std::list<prefab::CSoundSource*>	m_soundSources;		//!<サウンドソースのリスト。
		X3DAUDIO_CONE	m_emitterCone;
		CWaveFileBank m_waveFileBank;					//!<波形データのバンク。
		
	};
	static inline CSoundEngine& SoundEngine()
	{
		return CSoundEngine::Instance();
	}
}
