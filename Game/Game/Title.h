#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void OnDestroy()override;
	void Update() override;
	void PostDraw() override;
private:
	Sprite m_sprite;
	prefab::CSoundSource* m_titlebgm = nullptr;
	prefab::CSoundSource* m_decisionse = nullptr;
	bool SceneChenge = false;
};

