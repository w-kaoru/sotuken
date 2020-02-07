

#pragma once
#include "sound/WaveFileBank.h"

#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//�ő�o�̓`�����l�����B

/// <summary>
/// �T�E���h�G���W���B
/// </summary>
namespace GameEngine {
	class CWaveFile;
	namespace prefab {
		class CSoundSource;
	}
	class CSoundEngine {
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CSoundEngine();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CSoundEngine();

		/// <summary>
		/// �������B
		/// </summary>
		void Init();
		/// <summary>
		/// ���
		/// </summary>
		/// <remarks>
		/// �f�X�g���N�^����Ă΂�Ă��܂��B
		/// �����I�ɊJ���������ꍇ�Ɏg�p���Ă��������B
		/// </remarks>
		void Release();
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/*!
			* @brief	3D�T�E���h�\�[�X��ǉ��B
			*/
		void Add3DSoundSource(prefab::CSoundSource* s)
		{
			m_soundSources.push_back(s);
		}
		/*!
		* @brief	3D�T�E���h�\�[�X���폜�B
		*/
		void Remove3DSoundSource(prefab::CSoundSource* s)
		{
			auto it = std::find(m_soundSources.begin(), m_soundSources.end(), s);
			if (it != m_soundSources.end()) {
				m_soundSources.erase(it);
			}
		}
		/*!
		* @brief	�T�E���h���X�i�[�̍��W��ݒ�B
		* @details
		*  3D�������g���Ă��鎞�̌v�Z�Ɏg�p����܂��B
		*/
		void SetListenerPosition(const CVector3& pos)
		{
			m_listenerPosition = pos;
		}
		/*!
		* @brief	�T�E���h���X�i�[�̑O������ݒ�B
		* @details
		*  3D�������g���Ă��鎞�̌v�Z�Ɏg�p����܂��B
		*/
		void SetListenerFront(CVector3 front)
		{
			m_listener.OrientFront.x = front.x;
			m_listener.OrientFront.y = front.y;
			m_listener.OrientFront.z = front.z;
		}
		/*!
		* @brief	�T�E���h���X�i�[�̏������ݒ�B
		* @details
		*  3D�������g���Ă��鎞�̌v�Z�Ɏg�p����܂��B
		*/
		void SetListenerUp(CVector3 up)
		{
			m_listener.OrientTop.x = up.x;
			m_listener.OrientTop.y = up.y;
			m_listener.OrientTop.z = up.z;
		}
		/// <summary>
		/// XAudio2�̃\�[�X�{�C�X�̍쐬�B
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
		/// �o�̓`�����l���̐����擾�B
		/// </summary>
		/// <returns></returns>
		int GetNumChannel() const
		{
			return m_nChannels;
		}

		/// <summary>
		/// �g�`�f�[�^�o���N���擾�B
		/// </summary>
		CWaveFileBank& GetWaveFileBank()
		{
			return m_waveFileBank;
		}

		/*!
		 *@brief	�C���X�^���X�̎擾�B
		 */
		static CSoundEngine& Instance()
		{
			static CSoundEngine instance;
			return instance;
		}
	private:
		IXAudio2* m_xAudio2 = nullptr;
		IXAudio2MasteringVoice* m_masteringVoice = nullptr;
		X3DAUDIO_HANDLE m_hx3DAudio;					//!<3D�I�[�f�B�I�̃n���h���B
		IUnknown* m_reverbEffect = nullptr;				//!<���o�[�v�G�t�F�N�g�B
		IXAudio2SubmixVoice* m_submixVoice = nullptr;	//!<�T�u�~�b�N�X�{�C�X�B
		DWORD m_channelMask = 0;						//!<�I�[�f�B�I�`�����l���}�X�N�B
		DWORD m_nChannels = 0;							//!<�`�����l�����B
		CVector3 m_listenerPosition = CVector3::Zero();
		float m_fListenerAngle = 0.0f;
		bool m_UseListenerCone = false;
		bool m_fUseInnerRadius = false;
		bool m_useRedirectToLFE = false;
		bool m_isInited = false;
		X3DAUDIO_LISTENER m_listener;					//!<�T�E���h���X�i�[�B
		std::list<prefab::CSoundSource*>	m_soundSources;		//!<�T�E���h�\�[�X�̃��X�g�B
		X3DAUDIO_CONE	m_emitterCone;
		CWaveFileBank m_waveFileBank;					//!<�g�`�f�[�^�̃o���N�B
		
	};
	static inline CSoundEngine& SoundEngine()
	{
		return CSoundEngine::Instance();
	}
}
