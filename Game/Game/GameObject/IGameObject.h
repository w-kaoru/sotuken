#pragma once
typedef unsigned char	GameObjectPrio;
class IGameObject
{
public:
	virtual ~IGameObject();
	IGameObject() :
		m_priority(0),
		m_isStart(false),
		m_isDead(false)
	{
	}
	/*!
	*@brief	�������B
	*/
	virtual bool Start() { return true; }
	/*!
	*@brief	�X�V�B
	*/
	virtual void Update() {};
	/*!
	*@brief	�`��B
	*/
	virtual void Draw() {};
	/*!
	*@brief	�����B
	*/
	virtual void Destroy() {};

	/*!
	*@brief	Draw�֐������s�����O�ɌĂ΂��`�揈���B
	*/
	virtual void PreDraw() {};

	/*!
	*@brief	Draw�֐������s���ꂽ��ŌĂ΂��`�揈���B
	*/
	virtual void PostDraw() {};

	void StartWrapper() {

	}

	void UpdateWrapper() {

	}
	void DrawWrapper() {

	}
	void PreDrawWrapper() {

	}
	void PostDrawWrapper() {

	}
	//�I�u�W�F�N�g�̖��O�̃Q�b�^�[
	const std::string& GetName()const
	{
		return m_Name;
	}
	//�I�u�W�F�N�g�̖��O�̃Z�b�^�[
	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}
	/*!
	*@brief	���S�t���O�𗧂Ă�B
	*@details
	* ���̊֐��̓G���W���̊O����͎��s���Ȃ��ł��������B
	*/
	void SetDeadMark()
	{
		m_isDead = true;
	}
	friend class GameObjectManager;
protected:
	GameObjectPrio m_priority;			//!<���s�D��x
	bool m_isStart;						//!<Start�̊J�n�t���O�B
	bool m_isDead;						//!<���S�t���O�B
	std::string m_Name = "NULL";     	//!<�C���X�^���X�̖��O
};