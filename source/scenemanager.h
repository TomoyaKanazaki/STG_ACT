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
	void Uninit(SCENE next = NONE);
	void Update(void);
	void Draw(void);
	void SetNext(SCENE next);

	//�ÓI�����o�֐�
	static CSceneManager *Create(SCENE scene = TITLE);

private:

	//�����o�ϐ�
	SCENE m_Scene; //���݂̃Q�[�����[�h
	SCENE m_Next; //���̃Q�[�����[�h
	CScene *m_pScene; //�V�[���̃|�C���^
	CFade *m_pFade; //�t�F�[�h�̃|�C���^

};

#endif
