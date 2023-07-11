//==========================================
//
//  �Q�[���}�l�[�W���N���X(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "object_fan.h"
#include "score.h"
#include "timer.h"
#include "player.h"
#include "enemy_manager.h"
#include "light.h"
#include "camera.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CScore *CGameManager::m_pScore = NULL;
CTimer *CGameManager::m_pTimer = NULL;
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CGameManager::CGameManager()
{
	m_state = SHOT;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CGameManager::Init(void)
{
	//���̐���
	m_pFan = CObject_Fan::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 128, 1000.0f);

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 25.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�^�C�}�[�̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(187.5f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//�G�l�~�[�}�l�[�W���̐���
	CEnemyManager::Create();

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CGameManager::Uninit(void)
{
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
}

//==========================================
//  �X�V����
//==========================================
void CGameManager::Update(void)
{
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
void CGameManager::Draw(void)
{

}
