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
#include "player.h"
#include "enemy_manager.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"
#include "model.h"
#include "renderer.h"
#include "target.h"
#include "enemy.h"
#include "debugproc.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CGameManager::STATE CGameManager::m_State = NONE;
CPlayer *CGameManager::m_pPlayer = NULL;
CObject_Fan *CGameManager::m_pFan = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CTarget *CGameManager::m_pTarget = NULL;
CEnemyManager *CGameManager::m_pEnemy = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CGameManager::CGameManager()
{
	m_State = NONE;
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
	m_pFan = CObject_Fan::Create(D3DXVECTOR3(0.0f, 0.01f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 2000.0f);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�G�l�~�[�}�l�[�W���̐���
	m_pEnemy = CEnemyManager::Create();

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//�^�[�Q�b�g�𐶐�
	m_pTarget = CTarget::Create();

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
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
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

	//�t�F�[�Y�ڍs
	CManager::GetDebugProc()->Print("���j�� : %d\n", CEnemyManager::GetDeth());
	CManager::GetDebugProc()->Print("�t�F�[�Y : %d\n", m_State);

	if (CEnemyManager::GetDeth() >= m_State * 10 && m_State != BOSS_CREAR)
	{
		//�t�F�[�Y��i�߂�
		m_State = (CGameManager::STATE)((int)m_State + 1);

		//�G�����Z�b�g
		for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
		{
			//�I�u�W�F�N�g���擾
			CObject *pObj = CObject::GetTop(nCntPriority);

			//NULL�`�F�b�N
			while (pObj != NULL)
			{
				//���̃A�h���X��ۑ�
				CObject *pNext = pObj->GetNext();

				//�{�X�̏ꍇ
				if (pObj->GetType() != CObject::TYPE_ENEMY)
				{
					//���̃A�h���X�ɂ��炷
					pObj = pNext;
					continue;
				}

				//�G������
				pObj->Uninit();

				//���̃A�h���X�ɂ��炷
				pObj = pNext;
			}
		}

		//���j�������Z�b�g
		CEnemyManager::ResetDeth();

		if (m_State == BOSS_ATTACK)
		{
			for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
			{
				//�I�u�W�F�N�g���擾
				CObject *pObj = CObject::GetTop(nCntPriority);

				//NULL�`�F�b�N
				while (pObj != NULL)
				{
					//���̃A�h���X��ۑ�
					CObject *pNext = pObj->GetNext();

					//�{�X�̏ꍇ
					if (pObj->GetType() != CObject::TYPE_BOSS)
					{
						//���̃A�h���X�ɂ��炷
						pObj = pNext;
						continue;
					}

					//�{�X�����j����ʑJ�ڂ���
					pObj->Uninit();
					break;
				}
			}
		}
	}

	//�J��
	if (m_State == BOSS_CREAR)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
	}
}

//==========================================
//  �`�揈��
//==========================================
void CGameManager::Draw(void)
{

}
