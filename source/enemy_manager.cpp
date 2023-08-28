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
	m_nPopCounter[0] = 115;
	m_nPopCounter[1] = 110;
	m_nPopCounter[2] = 105;
	m_nPopCounter[3] = 100;
	m_nPopCounter[4] = 95;
	m_nPopCounter[5] = 90;
	m_nPopCounter[6] = 85;
	m_nPopCounter[7] = 80;
	m_nPopCounter[8] = 75;
	m_nPopCounter[9] = 70;
	m_nPopCounter[10] = 65;
	m_nPopCounter[11] = 60;
	m_nPopCounter[12] = 55;
	m_nPopCounter[13] = 50;
	m_nPopCounter[14] = 45;
	m_nPopCounter[15] = 40;
	m_nPopCounter[16] = 35;
	m_nPopCounter[17] = 30;
	m_nPopCounter[18] = 25;
	m_nPopCounter[19] = 20;
	m_nPopCounter[20] = 15;
	m_nPopCounter[21] = 10;
	m_nPopCounter[22] = 5;
	m_nPopCounter[23] = 0;
	m_nNumEnemy = 15;

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
	//���݂̎��Ԃ��擾
	m_nTime++;

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (m_nPopCounter[nCnt] * 60 == m_nTime && m_bPop[nCnt] == false)
		{
			for (int nCntEnemy = 0; nCntEnemy < m_nNumEnemy; nCntEnemy++)
			{
				//�������S���W�𐶐�
				m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
				m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

				//�G�𐶐�
				CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_NORMAL);
			}

			//���������t���O�𗧂Ă�
			m_bPop[nCnt] = true;
			break;
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
