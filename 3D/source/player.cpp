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
#include "target.h"
#include "bullet.h"
//#include "motion.h"
#include "collision.h"
#include "layer.h"
#include "gamemanager.h"
#include "orbit.h"

//==========================================
//  �}�N����`
//==========================================
#define PLAYER_SPEED (1.0f) //�v���C���[�̈ړ����x(�L�[�{�[�h)
#define TXTFILENAME_PLAYER "data\\TXT\\PlayerData.txt" //�v���C���[�����������e�L�X�g�t�@�C���̃p�X

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
	//m_pMotion = NULL;
	orbit = NULL;
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

	//orbit = COrbit::Create(m_ppModel[3], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50.0f, 50);

	////���[�V�������̐���
	//if (m_pMotion == NULL)
	//{
	//	m_pMotion = new CMotion;
	//}
	
	//���[�V�������Ƀ��f����ǉ�����
	//m_pMotion->SetModel(m_ppModel, m_nNumModel);

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

	////���[�V�����̃|�C���^��j��
	//if (m_pMotion != NULL)
	//{
	//	m_pMotion->Uninit();
	//	delete m_pMotion;
	//	m_pMotion = NULL;
	//}

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
			if (m_pShadow == NULL)
			{
				m_pShadow = CShadow::Create(m_pos, m_size, m_rot);
			}
		}
		else
		{
			return;
		}
	}

	//���n��Ԃ��擾
	m_bRand = CGameManager::GetFan()->OnMesh(m_pos);

	//�O����W�̕ۑ�
	D3DXVECTOR3 m_oldPos = m_pos;

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

	//��]����
	Rotate();

	//�X����
	Slop();

	//�e������
	if (CManager::GetMouse()->GetPress(CMouse::BUTTON_LEFT))
	{
		//�e�̈ړ��ʂ��Z�o
		D3DXVECTOR3 BulletMove = D3DXVECTOR3
		(
			-sinf(m_rot.y),
			0.0f,
			-cosf(m_rot.y)
		);

		//�e�̔��ˈʒu���Z�o
		D3DXVECTOR3 BulletPos = D3DXVECTOR3
		(
			m_pos.x + m_ppModel[3]->GetPos().x,
			10.0f,
			m_pos.z + m_ppModel[3]->GetPos().z
		);

		//�e�̐���
		CBullet::Create(BulletPos, m_size * 0.5f, BulletMove);
	}

	//�e�̏����X�V����
	if (m_pShadow != NULL)
	{
		m_pShadow->SetTransform(m_pos, m_rot);
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
	m_move += CManager::GetKeyboard()->GetWASD();
}

//==========================================
//  ��]����
//==========================================
void CPlayer::Rotate(void)
{
	//�}�E�X�J�[�\���ʒu�̎擾
	D3DXVECTOR2 CursorPos = CManager::GetMouse()->GetCursor();

	//�v���C���[�����̎擾
	m_fAngle = atan2f(-CursorPos.x, CursorPos.y);

	//�����]���p�ϐ�
	float fRotMove, fRotDest, fRotDiff;

	//���݂̊p�x�ƖړI�̊p�x�̍������v�Z
	fRotMove = m_rot.y;
	fRotDest = m_fAngle;
	fRotDiff = fRotDest - fRotMove;

	//�p�x�̕␳
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	//�����]���̊���
	fRotMove += fRotDiff * 0.5f;

	//�p�x�̕␳
	if (fRotMove > D3DX_PI)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove <= -D3DX_PI)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	//������K�p����
	m_rot.y = fRotMove;
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
