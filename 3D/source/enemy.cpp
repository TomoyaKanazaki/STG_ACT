//==========================================
//
//  �G�l�~�[�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "enemy.h"
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "model.h"
#include "shadow.h"
#include "motion.h"

//==========================================
//  �}�N����`
//==========================================
#define TXTFILENAME_ENEMY "data\\TXT\\EnemyData.txt" //�G�l�~�[�����������e�L�X�g�t�@�C���̃p�X

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nLife = 10;
	m_fSpeed = 0.0f;
	m_apModel = NULL;
	m_bRand = true;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_ENEMY);

	//���̂𐶐�
	Load();

	//�e�𐶐�
	m_pShadow = CShadow::Create(m_pos, m_size, m_rot);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	//���������J������
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_apModel != NULL)
		{
			if (m_apModel[nCnt] != NULL)
			{
				m_apModel[nCnt]->Uninit();
			}

			delete m_apModel;
			m_apModel = NULL;
		}
	}

	//�e�̍폜
	m_pShadow->Uninit();

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//�ړ��ʂ̓K�p
	m_pos += m_move;

	//���̂𓮂���
	m_apModel[0]->SetTransform(m_pos, m_rot);

	//�e�̏����X�V����
	m_pShadow->SetTransform(m_pos, m_rot);

	//���S����
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw()
{

}

//==========================================
//  �I�u�W�F�N�g��������
//==========================================
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, CEnemy::TYPE type)
{
	//�C���X�^���X����
	CEnemy *pEnemy = NULL;

	//NULL�`�F�b�N
	if (pEnemy == NULL)
	{
		//���������m��
		pEnemy = new CEnemy;
	}

	//�e����̕ۑ�
	pEnemy->m_pos = pos;
	pEnemy->m_size = size;
	pEnemy->m_rot = rot;

	//������
	if (pEnemy != NULL)
	{
		pEnemy->Init();
	}

	//�|�C���^��Ԃ�
	return pEnemy;
}

//==========================================
//  �G�l�~�[���̓ǂݍ���
//==========================================
void CEnemy::Load(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����
	char aStr[256]; //�s�v�ȕ�����̋L�^�p

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(TXTFILENAME_ENEMY, "r");

	if (pFile != NULL)
	{
		//�s�v�ȕ�����̓ǂݍ���
		for (int nCntDiscard = 0; nCntDiscard < 13; nCntDiscard++)
		{
			fscanf(pFile, "%s", &aStr[0]);
		}

		//���f�����̎擾
		fscanf(pFile, "%d", &m_nNumModel);

		//���f�������݂���ꍇ
		if (m_nNumModel > 0)
		{
			//�K�v�ȃ��������m�ۂ���
			if (m_apModel == NULL)
			{
				m_apModel = new CModel*[m_nNumModel];
			}
		}

		//���������m�ۂ����ꍇ
		if (m_apModel != NULL)
		{
			//�s�v�ȕ�����̓ǂݍ���
			for (int nCntDiscard = 0; nCntDiscard < 4; nCntDiscard++)
			{
				fscanf(pFile, "%s", &aStr[0]);
			}

			//�e���f���𐶐�����
			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				//���f�������p�ϐ�
				D3DXVECTOR3 pos, size = D3DXVECTOR3(0.0f, 5.0f, 0.0f), rot;
				int nModelID, nParentID;

				//�s�v�ȕ�����̓ǂݍ���
				for (int nCntDiscard = 0; nCntDiscard < 3; nCntDiscard++)
				{
					fscanf(pFile, "%s", &aStr[0]);
				}

				//�ʒu�����擾
				fscanf(pFile, "%f", &pos.x); fscanf(pFile, "%f", &pos.y); fscanf(pFile, "%f", &pos.z);

				//�s�v�ȕ�����̓ǂݍ���
				fscanf(pFile, "%s", &aStr[0]);

				//�p�x���擾
				fscanf(pFile, "%f", &rot.x); fscanf(pFile, "%f", &rot.y); fscanf(pFile, "%f", &rot.z);

				//�s�v�ȕ�����̓ǂݍ���
				fscanf(pFile, "%s", &aStr[0]);

				//�g�p���郂�f���̏����擾
				fscanf(pFile, "%d", &nModelID);

				//�s�v�ȕ�����̓ǂݍ���
				fscanf(pFile, "%s", &aStr[0]);

				//�e�̏����擾
				fscanf(pFile, "%d", &nParentID);

				//�擾������񂩂烂�f���𐶐�
				if (nParentID == -1)
				{
					m_apModel[nCnt] = CModel::Create(pos, size, rot, nModelID);
				}
				else
				{
					m_apModel[nCnt] = CModel::Create(pos, size, rot, nModelID, m_apModel[nParentID]);
				}
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{

	}
}
