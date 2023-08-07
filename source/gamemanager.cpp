//==========================================
//
//  �Q�[���}�l�[�W���N���X(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "manager.h"
#include "sound.h"
#include "object_fan.h"
#include "score.h"
#include "timer.h"
#include "player.h"
#include "enemy_manager.h"
#include "light.h"
#include "camera.h"
#include "energy.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CGameManager::STATE CGameManager::m_State = SHOT;
CScore *CGameManager::m_pScore = NULL;
CTimer *CGameManager::m_pTimer = NULL;
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CEnergy *CGameManager::m_pEnergy = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CGameManager::CGameManager()
{

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

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 25.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�^�C�}�[�̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(187.5f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120);

	//�G�l���M�[�̐���
	m_pEnergy = CEnergy::Create(D3DXVECTOR3(1200.0f, SCREEN_HEIGHT * 0.5f, 0.0f), 20.0f);

	//BGM�̍Đ�
	//CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CGameManager::Uninit(void)
{
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

	//BGM�̒�~
	CManager::GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CGameManager::Update(void)
{
#if _DEBUG
	//��ʑJ�ڃe�X�g
	if (CManager::GetKeyboard()->GetTrigger(DIK_0))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}
#endif

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

	if (m_State == SHOT)
	{
		if (m_pEnergy->IsMax())
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
			{
				m_State = BLADE;
			}
			CManager::GetDebugProc()->Print("\n�G�l���M�[MAX\n");
		}
		//�X�R�A�̔{���������鏈��
	}
	else if (m_State == BLADE)
	{
		if (m_pEnergy->IsMin())
		{
			m_State = SHOT;
		}
		//�G�l���M�[�����炷����
	}

	//��ʑJ��
	//if (m_pTimer->GetTime() <= 0)
	//{
	//	CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
	//	return;
	//}
}

//==========================================
//  �`�揈��
//==========================================
void CGameManager::Draw(void)
{

}
