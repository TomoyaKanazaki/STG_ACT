//==========================================
//
//  ��ʑJ�ڊǗ��N���X(scenemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "scenemanager.h"
#include "titlemanager.h"
#include "gamemanager.h"
#include "resultmanager.h"
#include "fade.h"
#include "scene.h"
#include "object.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CSceneManager::CSceneManager()
{
	m_Scene = NONE;
	m_pScene = NULL;
	m_pFade = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CSceneManager::~CSceneManager()
{

}

//==========================================
//  ����������
//==========================================
void CSceneManager::Init(SCENE newsecene)
{
	//�V�����V�[����ݒ�
	m_Scene = newsecene;

	//�V�[���𐶐�
	if (m_pScene == NULL)
	{
		switch (m_Scene)
		{
		case TITLE:
			m_pScene = new CTitleManager;
			break;
		case GAME:
			m_pScene = new CGameManager;
			break;
		case RESULT:
			m_pScene = new CResultManager;
			break;
		case RANKING:

			break;
		default:
			break;
		}
	}
	else
	{
		return;
	}

	//�V�[����������
	if (m_pScene != NULL)
	{
		m_pScene->Init();
	}

	//�t�F�[�h�𐶐�
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create(60, CFade::MODE_IN);
	}
}

//==========================================
//  �I������
//==========================================
void CSceneManager::Uninit(void)
{
	//�S�I�u�W�F�N�g��j��
	CObject::ReleaseAll();

	//�V�[�����I���A�j��
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = NULL;
	}
}

//==========================================
//  �X�V����
//==========================================
void CSceneManager::Update(void)
{
	//�V�[�����X�V
	if (m_pScene != NULL)
	{
		m_pScene->Update();
	}

	//�t�F�[�h���X�V
	if (m_pFade != NULL)
	{
		//�t�F�[�h������������폜����
		if (m_pFade->GetState() == true)
		{
			//�t�F�[�h���[�h��ۑ�
			CFade::MODE mode = m_pFade->GetMode();

			//�I���A�j��
			m_pFade->Uninit();
			delete m_pFade;
			m_pFade = NULL;

			//���̃V�[���𐶐�����
			if (mode == CFade::MODE_OUT)
			{
				Uninit();
				Init(m_Next);
			}
		}
	}
}

//==========================================
//  �`�揈��
//==========================================
void CSceneManager::Draw(void)
{
	//�V�[���̕`��
	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}

	//���݂̃V�[����\��
	switch (m_Scene)
	{
	case TITLE:
		CManager::GetDebugProc()->Print("���݂̃V�[�� : �^�C�g��\n");
		break;
	case GAME:
		CManager::GetDebugProc()->Print("���݂̃V�[�� : �Q�[��\n");
		break;
	case RESULT:
		CManager::GetDebugProc()->Print("���݂̃V�[�� : ���U���g\n");
		break;
	case RANKING:
		CManager::GetDebugProc()->Print("���݂̃V�[�� : �����L���O\n");
		break;
	default:
		break;
	}
}

//==========================================
//  �ݒ菈��
//==========================================
void CSceneManager::SetNext(SCENE next)
{
	//���̃V�[�����L�^
	m_Next = next;

	//�t�F�[�h�𐶐�
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create(60, CFade::MODE_OUT);
	}
}

//==========================================
//  ��������
//==========================================
CSceneManager *CSceneManager::Create(SCENE scene)
{
	//�C���X�^���X����
	CSceneManager *pScene = NULL;

	//NULL�`�F�b�N
	if (pScene == NULL)
	{
		//���������m��
		pScene = new CSceneManager;
	}

	//������
	if (pScene != NULL)
	{
		pScene->Init(scene);
	}

	//�|�C���^��Ԃ�
	return pScene;
}
