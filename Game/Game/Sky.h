#pragma once
class Sky:public IGameObject
{
public:
	Sky();
	~Sky();
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// 分割描画関数
	/// </summary>
	void Draw(int player_num);
	/// <summary>
	/// スケールを再設定する関数
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ポジションをセットする関数
	/// </summary>
	/// <param name="pos">ポジション(CVector3)</param>
	void SetPositon(CVector3& pos)
	{
		m_position = pos;
	}

private:
	SkinModel m_skymodel;
	CVector3 m_scale = CVector3::One();
	CVector3 m_position = CVector3::Zero();
	ID3D11ShaderResourceView*	m_srv = nullptr;	//SRV
	bool						m_isValid = false;	//有効かどうかのフラグ
};

