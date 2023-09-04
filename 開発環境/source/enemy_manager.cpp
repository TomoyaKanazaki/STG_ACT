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
//  �}�N����`
//==========================================
#define ENEMY_FILEPASS "data\\BIN\\EnemyData.bin"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEnemyManager::m_nDead = 0;
int CEnemyManager::m_nNumData = 0;
CEnemyManager::CreateData *CEnemyManager::m_pCreateData = NULL;

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
	//�o�߃t���[�������Z
	//m_nTime++;

	//���݂̃t�F�[�Y���擾
	int nFaze = (int)CGameManager::GetState();

	//�G�l�~�[�f�[�^���Q��
	for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
	{
		//���������t�F�[�Y���Q�Ƃ���
		if (nFaze == m_pCreateData[nCnt].fase)
		{
			//�����񐔂��Q�Ƃ���
			if (m_pCreateData[nCnt].nCount > 0 || m_pCreateData[nCnt].nCount == -1)
			{
				//�����t���[�����Q�Ƃ���
				if (m_nTime % m_pCreateData[nCnt].nInterval == 0)
				{
					//�G�𐶐�
					CEnemy::Create(m_pCreateData[nCnt].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (CEnemy::TYPE)m_pCreateData[nCnt].type);

					//�����񐔂����炷
					if (m_pCreateData[nCnt].nCount != -1)
					{
						m_pCreateData[nCnt].nCount--;
					}
				}
			}
		}
	}

#ifdef _DEBUG
	//�ڋ߂���G
	if (CManager::GetKeyboard()->GetTrigger(DIK_E))
	{
		for (int nCntEnemy = 0; nCntEnemy < 3; nCntEnemy++)
		{
			//�������S���W�𐶐�
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//�G�𐶐�
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_NORMAL);
		}
	}
	
	//�ˌ�����G
	if (CManager::GetKeyboard()->GetTrigger(DIK_Q))
	{
		for (int nCntEnemy = 0; nCntEnemy < 3; nCntEnemy++)
		{
			//�������S���W�𐶐�
			m_pos = D3DXVECTOR3((float)(rand() % 600 - 300), 0.0f, 0.0f);
			m_pos = D3DXVECTOR3(m_pos.x, 0.0f, -600.0f);

			//�G�𐶐�
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::TYPE_SHOT);
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

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CEnemyManager::Load(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(ENEMY_FILEPASS, "rb");

	if (pFile != NULL)
	{
		//�ۑ�����Ă���f�[�^�����擾����
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//�K�v���̃��������m�ۂ���
		m_pCreateData = new CreateData[m_nNumData];

		//�ۑ�����Ă���f�[�^��S�ēǂݍ���
		for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
		{
			fread(&m_pCreateData[nCnt], sizeof(CreateData), 1, pFile);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CEnemyManager::Load(char *aPass)
{
	//�t�@�C�����������ݐ�p�ŊJ��
	FILE *pFile = fopen(aPass, "rb");

	if (pFile != NULL)
	{
		//�ۑ�����Ă���f�[�^�����擾����
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//�K�v���̃��������m�ۂ���
		m_pCreateData = new CreateData[m_nNumData];

		//�ۑ�����Ă���f�[�^��S�ēǂݍ���
		for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
		{
			fread(&m_pCreateData[nCnt], sizeof(CreateData), 1, pFile);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//==========================================
//  �f�[�^�̔j��
//==========================================
void CEnemyManager::Unload(void)
{
	if (m_pCreateData != NULL)
	{
		delete[] m_pCreateData;
		m_pCreateData = NULL;
	}
}
