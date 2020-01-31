#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title(); bool Start() override;
	void Update() override;
	void PostDraw() override;
private:
	Sprite m_sprite;
	CSoundSource m_decisionse;
	bool SceneChenge = false;
};

