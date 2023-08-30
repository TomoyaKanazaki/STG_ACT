//==========================================
//
//  �G�l�~�[�}�l�[�W���N���X(enemy_manager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_manager.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEnemyManager::m_nDead = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyManager::CEnemyManager()
{
	m_vecError = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_nPopCounter[nCnt] = 0;
		m_bPop[nCnt] = false;
	}
	m_nNumEnemy = 0;
	m_nTime = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyManager::Init(void)
{
	//�O���t�@�C������ǂݍ���
	m_vecError = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	m_nNumEnemy = 15;

	//�{�X��z�u
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_BOSS);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemyManager::Uninit(void)
{
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyManager::Update(void)
{
	m_nTime++;
	if (m_nTime % 60 == 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < m_nNumEnemy; nCntEnemy++)
		{
			//�������S���W�𐶐�
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//�G�𐶐�
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_NORMAL);
		}
	}

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		for (int nCntEnemy = 0; nCntEnemy < m_nNumEnemy; nCntEnemy++)
		{
			//�������S���W�𐶐�
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//�G�𐶐�
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_NORMAL);
		}
	}
#endif
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyManager::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CEnemyManager *CEnemyManager::Create(void)
{
	//�C���X�^���X����
	CEnemyManager *pEnemyManager = NULL;

	//NULL�`�F�b�N
	if (pEnemyManager == NULL)
	{
		//���������m��
		pEnemyManager = new CEnemyManager;
	}

	//������
	if (pEnemyManager != NULL)
	{
		pEnemyManager->Init();
	}

	//�|�C���^��Ԃ�
	return pEnemyManager;
}
