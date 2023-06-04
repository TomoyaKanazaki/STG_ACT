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
#include "bullet.h"
#include "debugproc.h"
#include "enemy.h"
#include "explosion.h"
#include "bg.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CJoyPad *CManager::m_pJoyPad[MAX_PLAYER] = {};
CDebugProc *CManager::m_pDebugProc = NULL;

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

	//�e�N�X�`���̓ǂݍ���
	CPlayer::Load();
	CEnemy::Load();
	CBullet::Load();
	CExplosion::Load();
	CBg::Load();

	//�v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	//�L�[�{�[�h�̏I���A�j��
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	//�e�N�X�`���̔j��
	CPlayer::UnLoad();
	CEnemy::UnLoad();
	CBullet::UnLoad();
	CExplosion::UnLoad();
	CBg::UnLoad();
}

//==========================================
//  �X�V����
//==========================================
void CManager::Update(void)
{
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

	//�G�̐���
	if (CEnemy::GetNum() == 0 || m_pKeyboard->GetTrigger(DIK_RETURN))
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.3f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.4f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.7f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.9f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
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
