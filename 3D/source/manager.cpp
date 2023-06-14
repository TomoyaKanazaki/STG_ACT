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
#include "player.h"
#include "debugproc.h"
#include "effect.h"
#include "score.h"
#include "timer.h"
#include "number.h"
#include "pause.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "field.h"
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CJoyPad *CManager::m_pJoyPad[MAX_PLAYER] = {};
CDebugProc *CManager::m_pDebugProc = NULL;
CPause *CManager::m_pPause = NULL;
CScore *CManager::m_pScore = NULL;
CTimer *CManager::m_pTimer = NULL;
CSound *CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CTexture *CManager::m_pTexture = NULL;

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

	////�W���C�p�b�h�̐���
	//if (m_pJoyPad[0] == NULL)
	//{
	//	m_pJoyPad[0] = new CJoyPad;
	//}

	////�W���C�p�b�h�̏�����
	//if (m_pJoyPad[0] != NULL)
	//{
	//	if (FAILED(m_pJoyPad[0]->Init(hInstance, hWnd)))
	//	{
	//		return E_FAIL;
	//	}
	//}

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

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 25.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�^�C�}�[�̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(187.5f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	//���̐���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
		m_pSound->Stop();
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
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

	//�|�[�Y�̏I���A�j��
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

	//�X�R�A�̏I���A�j��
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}

	//�^�C�}�[�̏I���A�j��
	if (m_pTimer != NULL)
	{
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = NULL;
	}

	//�J�����̏I���A�j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//���C�g�̏I���A�j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->UnLoad();
		delete m_pTexture;
		m_pTexture = NULL;
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

	//�J�����̍X�V
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
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
