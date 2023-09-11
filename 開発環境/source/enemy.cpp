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
#include "motion.h"
#include "particle.h"
#include "enemy_manager.h"
#include "object_fan.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"

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
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_LAYER);

	//���f���p�̃������̊m��
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//�K�v�ȃ��f���𐶐�
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//��ɂ���
		m_ppModel[nCnt] = NULL;

		//�e�����݂��Ȃ��ꍇ
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//���[�V�������̐���
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}

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
	//�O��̍��W��ۑ�����
	m_oldPos = m_pos;

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
	
	//�ړ��ʂ̓K�p
	m_pos += m_move;

	//�������玀��
	if (m_pos.y < -5000.0f)
	{
		//�p�[�e�B�N�����Ăяo��
		CParticle::Create(m_pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(0.98f, 0.87f, 0.28f, 0.5f), 10, 30, 10, 5);

		Uninit();
	}

	//�����痎����
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
		return;
	}

	//�ړ��̏���
	if (this->GetType() == CObject::TYPE_ENEMY) //�v���C���[�ǂ�����
	{
		//�ړ�
		Move();

		//�v���C���[���E��
		Collision::CollisionPlayer(m_pos, 30.0f);
	}
	else
	{
		//�����ɂ��ړ��̒�~
		m_move.x += (0.0f - m_move.x) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;

		//�A���̔���
		Chain();

		//���Ԃ̃J�E���g
		m_nCntBullet++;

		//��莞�Ԍo�߂œG�ɖ߂�
		if (m_nCntBullet >= 30 || (fabsf(m_move.x) <= 0.1f && fabsf(m_move.z) <= 0.1f))
		{
			m_nCntBullet = 0;
			this->SetType(CObject::TYPE_ENEMY);
		}
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
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CEnemy *pEnemy = NULL;

	//NULL�`�F�b�N
	if (pEnemy == NULL)
	{
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

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_ENEMY) && pObj != this) //�G�̏ꍇ
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

			if ((pObj->GetType() == CObject::TYPE_BULLET_ENEMY || pObj->GetType() == CObject::TYPE_ENEMY) && pObj != this)
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

					//�ՓˑΏۂ͘A�����Ȃ��e�ɂȂ�
					pObj->SetType(CObject::TYPE_BULLET_ENEMY);

					//�ՓˑΏۂ̑��x���擾
					D3DXVECTOR3 moveObj = pObj->GetMove();

					//�ՓˑΏۂ̈ړ��ʂƎ��g�̈ړ��ʂ̍��������߂�
					D3DXVECTOR3 vecSab = m_move - moveObj;

					//�O����W
					D3DXVECTOR3 vecToOld = m_oldPos - posObj;

					//�x�N�g���𐳋K��
					D3DXVec3Normalize(&vecToOld, &vecToOld);

					//�x�N�g���̓���
					float fDot = D3DXVec3Dot(&vecSab, &vecToOld);

					//�����萔
					D3DXVECTOR3 vecConst = (fDot * 0.5f) * vecToOld;

					//�Փˌ㑬�x�x�N�g���̎Z�o
					m_move = (vecConst + m_move);
					pObj->SetMove(vecConst + moveObj);

					//�Փˌ�ʒu�̎Z�o
					m_pos = m_pos + (m_move * 3.0f);
					pObj->SetPos(posObj + (pObj->GetMove() * 3.0f));
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
