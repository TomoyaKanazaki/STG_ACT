//==========================================
//
//  �}�l�[�W���N���X(manager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "object2D.h"
#include "debugproc.h"
#include "pause.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "layer.h"
#include "gamemanager.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CJoyPad *CManager::m_pJoyPad = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CPause *CManager::m_pPause = NULL;
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CGameManager *CManager::m_pGameManager = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CManager::CManager()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CManager::~CManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	//�����_���[�̏�����
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return E_FAIL;
		}
	}
	
	//�T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//�T�E���h�̏�����
	if (m_pSound != NULL)
	{
		if (FAILED(m_pSound->Init(hWnd)))
		{
			return E_FAIL;
		}
	}

	//�e�N�X�`���̓ǂݍ���
	if (m_pTexture == NULL)
	{
		//�C���X�^���X����
		m_pTexture = new CTexture;

		//�ǂݍ��݂��ς�ł��邩�ۂ�
		if (m_pTexture != NULL)
		{
			if (CTexture::GetLoadState() == false)
			{
				//�e�N�X�`����ǂݍ���
				m_pTexture->Load();
			}
		}
	}

	//���f���̓ǂݍ���
	if (CModel::GetLoadState() == false)
	{
		//���f����ǂݍ���
		CModel::Load();
	}

	//�K�w�\����ǂݍ���
	CLayer::Load();

	//�f�o�b�O�\���̐���
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = new CDebugProc;
	}

	//�f�o�b�O�\���̏�����
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Init();
	}

	//�L�[�{�[�h�̐���
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}

	//�L�[�{�[�h�̏�����
	if (m_pKeyboard != NULL)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//�}�E�X�̐���
	if (m_pMouse == NULL)
	{
		m_pMouse = new CMouse;
	}

	//�}�E�X�̏�����
	if (m_pMouse != NULL)
	{
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//�W���C�p�b�h�̐���
	if (m_pJoyPad == NULL)
	{
		m_pJoyPad = new CJoyPad;
	}

	//�W���C�p�b�h�̏�����
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Init(hInstance, hWnd);
	}

	//�|�[�Y�̐���
	if (m_pPause == NULL)
	{
		m_pPause = new CPause;
	}

	//�|�[�Y�̏�����
	if (m_pPause != NULL)
	{
		if (FAILED(m_pPause->Init()))
		{
			return E_FAIL;
		}
	}

	//�Q�[���}�l�[�W���̐���
	if (m_pGameManager == NULL)
	{
		m_pGameManager = new CGameManager;
	}

	//�|�[�Y�̏�����
	if (m_pGameManager != NULL)
	{
		if (FAILED(m_pGameManager->Init()))
		{
			return E_FAIL;
		}
	}

	//BGM�̍Đ�
	m_pSound->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CManager::Uninit(void)
{
	//�I�u�W�F�N�g�̏I��
	CObject::ReleaseAll();

	//�����_���[�̏I���A�j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�T�E���h�̏I���A�j��
	if (m_pSound != NULL)
	{
		m_pSound->Stop();
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�f�o�b�O�\���̏I���A�j��
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	//�L�[�{�[�h�̏I���A�j��
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//�}�E�X�̏I���A�j��
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}
	
	//�W���C�p�b�h�̏I���A�j��
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = NULL;
	}

	//�|�[�Y�̏I���A�j��
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->UnLoad();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//���f����j��
	if (CModel::GetLoadState())
	{
		//���f����j��
		CModel::UnLoad();
	}

	//�K�w�\����j��
	CLayer::UnLoad();

	//�Q�[���}�l�[�W���̏I���A�j��
	if (m_pGameManager != NULL)
	{
		m_pGameManager->Uninit();
		delete m_pGameManager;
		m_pGameManager = NULL;
	}
}

//==========================================
//  �X�V����
//==========================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	//�}�E�X�̍X�V����
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
	
	//�W���C�p�b�h�̍X�V����
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Update();
	}

	//�|�[�Y�̍X�V����
	if (m_pPause != NULL)
	{
		m_pPause->Update();
	}

	//�����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//�f�o�b�O�\���̍X�V����
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Update();
	}

	//�Q�[���}�l�[�W���̍X�V
	if (m_pGameManager != NULL)
	{
		m_pGameManager->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}
