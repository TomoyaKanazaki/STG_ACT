//==========================================
//
//  �G�l�~�[�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "enemy.h"
#include "player.h"
#include "gamemanager.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "model.h"
#include "motion.h"
#include "particle.h"
#include "enemy_manager.h"
#include "object_fan.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "enemy_normal.h"
#include "enemy_block.h"
#include "enemy_push.h"
#include "smoke.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CEnemy::mc_fSize = 75.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nCntBullet = 0;
	m_nCombo = 1;
	m_fSpeed = 0.0f;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
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
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	//���f���̃|�C���^��j��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//���[�V�������̔j��
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//���̂��ړ�����
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				if (m_ppModel[nCnt]->GetParent() == NULL)
				{
					m_ppModel[nCnt]->SetTransform(m_pos, m_rot);
				}
			}
		}
	}

	//�����痎����
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
	}

	//�e��Ԃɉ���t����
	if (this->GetType() == CObject::TYPE_BULLET_ENEMY)
	{
		CSmoke::Create(m_pos, m_size * 1.5f, D3DXCOLOR(1.0f, 1.0f - (0.12f * m_nCombo), 0.0f, 1.0f), 10);
	}

	//�O��̍��W��ۑ�����
	m_oldPos = m_pos;
	
	//�ړ��ʂ̓K�p
	m_pos += m_move;

	//�������玀��
	if (m_pos.y < -5000.0f)
	{
		//�p�[�e�B�N�����Ăяo��
		CParticle::Create(m_pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);

		Uninit();
	}

	//�G���m�̔���
	AvertEnemy();
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
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, ENEMY_TYPE type)
{
	//�C���X�^���X����
	CEnemy *pEnemy = NULL;

	//NULL�`�F�b�N
	if (pEnemy == NULL)
	{
		switch (type)
		{
		case NORMAL:
			pEnemy = new CEnemy_Normal;
			break;
		case BLOCK:
			pEnemy = new CEnemy_Block;
			break;
		case PUSH:
			pEnemy = new CEnemy_Push;
			break;
		default:
			return NULL;
		}
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
//  �G���m���Ԃ��锻��
//==========================================
void CEnemy::AvertEnemy(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�����̃A�h���X���擾
		CObject *pObj = this->GetNext();

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_NORMAL_ENEMY) && pObj != this) //�G�̏ꍇ
			{
				//���݂̓G�Ǝ��������ԃx�N�g�����擾����
				D3DXVECTOR3 posObj = pObj->GetPos();
				D3DXVECTOR3 vecToObj = m_pos - posObj;

				//�x�N�g���̑傫�����Z�o
				float fLength = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);

				//�ڐG�͈͓��ɂ����ꍇ
				if (fLength < mc_fSize * mc_fSize)
				{
					//�ړ_���W�����߂�
					D3DXVECTOR3 contact = (posObj + m_pos) * 0.5f;

					//�x�N�g���̊p�x�����߂�
					float rotVector = atan2f(vecToObj.x, vecToObj.z);

					//x,z�̕␳�l�����߂�
					D3DXVECTOR2 correction = { sinf(rotVector), cosf(rotVector) };

					//���W��␳����
					m_pos.x = correction.x * (mc_fSize * 0.5f) + contact.x;
					m_pos.z = correction.y * (mc_fSize * 0.5f) + contact.z;
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}

//==========================================
//  �A���̔���
//==========================================
void CEnemy::Chain(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�����̃A�h���X���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_NORMAL_ENEMY) && pObj != this)
			{
				//���݂̓G�Ǝ��������ԃx�N�g�����擾����
				D3DXVECTOR3 posObj = pObj->GetPos();
				D3DXVECTOR3 vecToObj = m_pos - posObj;

				//�x�N�g���̑傫�����Z�o
				float fLength = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);

				//�ڐG�͈͓��ɂ����ꍇ
				if (fLength < mc_fSize * mc_fSize)
				{
					//�R���{�������Z
					m_nCombo++;

					//�ՓˑΏۂ͒e�ɂȂ�
					pObj->SetType(CObject::TYPE_BULLET_ENEMY);

					//�ՓˑΏۂɈړ��ʂ������t����
					pObj->SetMove(m_move * 1.5f);

					//�����͓G�ɖ߂�
					this->SetType(CObject::TYPE_NORMAL_ENEMY);
					m_nCntBullet = 0;
				}
			}
			
			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}

//==========================================
//  �v���C���[�Ɍ���������
//==========================================
void CEnemy::Move(void)
{
	//�v���C���[�̍��p���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�Ɍ������x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//�v���C���[�̕���������
	float fRot = atan2f(-vecToPlayer.x, -vecToPlayer.z);
	m_rot.y = fRot;

	//�x�N�g���𐳋K��
	vecToPlayer.y = 0.0f;
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//�ړ��ʂ�K�p
	m_move = vecToPlayer * 5.0f;
}
