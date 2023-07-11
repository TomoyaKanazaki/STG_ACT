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
#include "item.h"

//==========================================
//  �}�N����`
//==========================================
#define TXTFILENAME_ENEMY "data\\TXT\\EnemyData.txt" //�G�l�~�[�����������e�L�X�g�t�@�C���̃p�X

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEnemy::m_nCntEnemy = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_fSpeed = 0.0f;
	m_apModel = NULL;
	m_pLayer = NULL;
	m_pShadow = NULL;
	m_bRand = true;
	m_nCntEnemy++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{
	m_nCntEnemy--;
}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	//�K�v�ȃ��f���𐶐�
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_apModel[nCnt] = *CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_apModel[nCnt] = *CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], &m_apModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//�e�𐶐�
	if (m_pShadow == NULL)
	{
		m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	//�e���f�����J������
	if (m_apModel != NULL)
	{
		m_apModel->Uninit();
		delete[] m_apModel;
		m_apModel = NULL;
	}

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
	m_apModel[0].SetTransform(m_pos, m_rot);

	//�e�̏����X�V����
	m_pShadow->SetTransform(m_pos, m_rot);
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
