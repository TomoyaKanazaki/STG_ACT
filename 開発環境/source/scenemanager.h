//==========================================
//
//  ��ʑJ�ڊǗ��N���X(scenemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "main.h"

//==========================================
//  �O���錾
//==========================================
class CScene;
class CFade;
class CCamera;

//==========================================
//  ��ʑJ�ڃN���X��`
//==========================================
class CSceneManager
{
public:
	enum SCENE
	{
		NONE = 0,
		TITLE,
		GAME,
		RESULT,
		RANKING,
		MAX
	};

	CSceneManager(); //�R���X�g���N�^
	~CSceneManager(); //�f�X�g���N�^

	//�����o�֐�
	void Init(SCENE newsecene);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNext(SCENE next);

	//�ÓI�����o�֐�
	static CScene *GetScene(void) { return m_pScene; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CSceneManager *Create(SCENE scene = TITLE);

private:

	//�����o�ϐ�
	SCENE m_Scene; //���݂̃Q�[�����[�h
	SCENE m_Next; //���̃Q�[�����[�h
	CFade *m_pFade; //�t�F�[�h�̃|�C���^

	//�ÓI�����o�ϐ�
	static CScene *m_pScene; //�V�[���̃|�C���^
	static CCamera *m_pCamera; //�J�����̃|�C���^

};

#endif
