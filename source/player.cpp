//==========================================
//
//  �v���C���[�N���X(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "field.h"
#include "object_fan.h"
#include "collision.h"
#include "bullet.h"
#include "motion.h"
#include "collision.h"
#include "layer.h"
#include "gamemanager.h"
#include "orbit.h"
#include "particle.h"
#include "camera.h"

//==========================================
//  �}�N����`
//==========================================
#define PLAYER_SPEED (1.0f) //�v���C���[�̈ړ����x(�L�[�{�[�h)

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CPlayer::mc_fExplosion = 5000.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_nLife = 0;
	m_nDeadCounter = 0;
	m_fSpeed = 0.0f;
	m_fAngle = 0.0f;
	m_bRand = true;
	m_bDead = false;
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pShadow = NULL;
	m_pMotion = NULL;
	m_orbit = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CPlayer::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_PLAYER);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

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
	
	//���[�V�������Ƀ��f����ǉ�����
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_SHOT);

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
void CPlayer::Uninit(void)
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

	//���[�V�����̃|�C���^��j��
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�O�Ղ�j��
	if (m_orbit != NULL)
	{
		m_orbit->Uninit();
		delete m_orbit;
		m_orbit = NULL;
	}

	//�e�̃|�C���^��j��
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	//���S�m�F
	if (m_bDead)
	{
		//���S�J�E���^�[�̉��Z
		m_nDeadCounter++;

		//���S�����莞�Ԍo�߂��Ă�����h������
		if (m_nDeadCounter >= 60)
		{
			m_bDead = false;
			m_nDeadCounter = 0;
			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Explosion();
			if (m_pShadow == NULL)
			{
				m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
			}
			return;
		}
		else
		{
			return;
		}
	}

	//���S����
	if (m_pos.y < -1000.0f || Collision::CollisionEnemy(m_pos, 30.0f, false))
	{
		m_nLife--;
		m_bDead = true;
		if (m_pShadow != NULL)
		{
			m_pShadow->Uninit();
			m_pShadow = NULL;
		}
		if (m_orbit != NULL)
		{
			m_orbit->Uninit();
			delete m_orbit;
			m_orbit = NULL;
		}
		CGameManager::SetState(CGameManager::NONE);
	}

	//�O����W�̕ۑ�
	m_oldPos = m_pos;

	//�O��p�x�̕ۑ�
	m_oldRot = m_rot;

	//���n��Ԃ��擾
	m_bRand = CGameManager::GetFan()->OnMesh(m_pos);

	//���݈ʒu�̔���
	if (m_bRand)
	{
		//�ړ�����
		Move();
	}
	else
	{
		//����
		m_move.y += -0.5f;
		if (m_pShadow != NULL)
		{
			m_pShadow->Uninit();
			m_pShadow = NULL;
		}
	}

	//�ړ��ʂ̓K�p
	m_pos += m_move;

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

	//�X����
	Slop();

	//�r����
	Swing();

	//�r����
	Aiming();

	//���[�V�������X�V����
	m_pMotion->Update();

	//�U��
	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		Shot();
	}

	//�O�Ղ̐����A�폜
	if (CManager::GetMouse()->GetTrigger(CMouse::BUTTON_RIGHT))
	{
		if (m_orbit == NULL)
		{
			m_orbit = COrbit::Create(m_ppModel[4], D3DXCOLOR(0.0f, 1.0f, 0.1f, 0.7f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-200.0f, 0.0f, 0.0f), 10);
		}
	}
	else if (CManager::GetMouse()->GetRelease(CMouse::BUTTON_RIGHT))
	{
		if (m_orbit != NULL)
		{
			m_orbit->Uninit();
			delete m_orbit;
			m_orbit = NULL;
		}
	}

	//�e�̏����X�V����
	if (m_pShadow != NULL)
	{
		m_pShadow->SetTransform(m_pos, m_rot);
	}

	//��l�̕�
	if (m_pos.z > 130.0f)
	{
		m_pos.z = 130.0f;
	}

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("�v���C���[���W : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("�v���C���[���� : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("�v���C���[�ړ��� : ( %f, %f, %f )\n", m_move.x, m_move.y, m_move.z);
	CManager::GetDebugProc()->Print("�v���C���[�̗� : %d\n", m_nLife);
}

//==========================================
//  �`�揈��
//==========================================
void CPlayer::Draw()
{

}

//==========================================
//  �I�u�W�F�N�g��������
//==========================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CPlayer *pPlayer = NULL;

	//NULL�`�F�b�N
	if (pPlayer == NULL)
	{
		//���������m��
		pPlayer = new CPlayer;
	}

	//�e����̕ۑ�
	pPlayer->m_pos = pos;
	pPlayer->m_size = size;
	pPlayer->m_rot = rot;

	//������
	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	//�|�C���^��Ԃ�
	return pPlayer;
}

//==========================================
//  �ړ�����
//==========================================
void CPlayer::Move(void)
{
	//�����ɂ��ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//�ړ��ʂ̎擾
	D3DXVECTOR3 move = CManager::GetKeyboard()->GetWASD();

	//�ړ��ʂ�K�p
	m_move += move;
}

//==========================================
//  �ړ������ɌX����
//==========================================
void CPlayer::Slop(void)
{
	//�v�Z�p�ϐ��錾
	float rot = m_rot.y + D3DX_PI;
	D3DXVECTOR3 move = m_move;

	//Y���̕␳
	move.x = m_move.z * cosf(rot) + m_move.x * sinf(rot);
	move.z = m_move.z * sinf(rot) + -m_move.x * cosf(rot);

	//�p�x���Z�o
	m_rot.x = atan2f(-move.x, 30.0f);
	m_rot.z = atan2f(-move.z, 30.0f);
}

//==========================================
//  �ˌ�
//==========================================
void CPlayer::Shot(void)
{
	//�e�̔��ˈʒu���Z�o
	D3DXVECTOR3 BulletPos = D3DXVECTOR3
	(
		m_ppModel[3]->GetMtx()._41,
		m_ppModel[3]->GetMtx()._42,
		m_ppModel[3]->GetMtx()._43
	);

	//�J�����̒����_���擾
	D3DXVECTOR3 vecPosR = CGameManager::GetCamera()->GetPosR();

	//�ړ��ʂ��Z�o
	D3DXVECTOR3 BulletMove = vecPosR - BulletPos;
	BulletMove.y = 0.0f;
	D3DXVec3Normalize(&BulletMove, &BulletMove);
	BulletMove *= 5.0f;

	//�e�̐���
	CBullet::Create(BulletPos, m_size * 0.5f, BulletMove, CBullet::PLAYER, CBullet::HOMING_BULLET);
}

//==========================================
//  �������ɔ������ēG��|������
//==========================================
void CPlayer::Explosion(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�����̃A�h���X���擾
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY || pObj->GetType() == CObject::TYPE_BULLET) //�G�̏ꍇ
			{
				//�߂��ɂ��邩�̔���
				D3DXVECTOR3 vecToObj = m_pos - pObj->GetPos();
				float fLengh = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);
				if (fLengh < mc_fExplosion * mc_fExplosion)
				{
					//�E��
					pObj->Uninit();
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}

//==========================================
//  �r��U�鏈��
//==========================================
void CPlayer::Swing(void)
{
	//�}�E�X�̉������̈ړ��ʂ��擾����
	float fMove = CManager::GetMouse()->GetMouseMove().x;

	//�p�x���擾
	D3DXVECTOR3 rot = m_ppModel[4]->GetRot();

	//�r�̊p�x��ς���
	rot.y += -fMove;

	//�p�x�̕␳
	if (rot.y < -2.7f)
	{
		rot.y = -2.7f;
	}
	if (rot.y > 0.0f)
	{
		rot.y = 0.0f;
	}

	//�p�x��K�p
	m_ppModel[4]->SetRot(rot);
}

//==========================================
//  �_������
//==========================================
void CPlayer::Aiming(void)
{
	//���[�J���ϐ��錾
	D3DXMATRIX mtx = m_ppModel[3]->GetMtx();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent; //�e�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_ppModel[3]->GetPos().x, m_ppModel[3]->GetPos().y, m_ppModel[3]->GetPos().z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	//�e�}�g���b�N�X�̐ݒ�
	mtxParent = m_ppModel[3]->GetParent()->GetMtx();

	//���[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
	D3DXMatrixMultiply
	(
		&mtx,
		&mtx,
		&mtxParent
	);

	//���W�𒊏o
	D3DXVECTOR3 pos = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);

	//�J�����̒����_���擾
	D3DXVECTOR3 rotCamera = CGameManager::GetCamera()->GetRot();

	//���f���̊p�x���擾
	D3DXVECTOR3 rot = m_ppModel[3]->GetRot();
	rot.y = rotCamera.y;

	//�p�x��K�p
	m_ppModel[3]->SetRot(rot);
}
