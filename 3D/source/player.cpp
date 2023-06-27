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
#include "object_mesh.h"
#include "collision.h"

//==========================================
//  �}�N����`
//==========================================
#define PLAYER_SPEED (1.0f) //�v���C���[�̈ړ����x(�L�[�{�[�h)
#define TXTFILENAME_PLAYER "data\\TXT\\PlayerData.txt" //�v���C���[�����������e�L�X�g�t�@�C���̃p�X
#define SHARE_PASS_PLAYER "data\\MODEL\\Player\\" //�S�Ẵv���C���[���f���t�@�C���ɋ��ʂ��鑊�΃p�X

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
	m_apModel = NULL;
	m_bRand = true;
	m_bDead = false;
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
HRESULT CPlayer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�e����̕ۑ�
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//�^�C�v�̐ݒ�
	SetType(TYPE_PLAYER);

	//���̂𐶐�
	Load();

	//�e�𐶐�
	m_pShadow = CShadow::Create(m_pos, m_size, m_rot);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CPlayer::Uninit(void)
{
	if (m_apModel != NULL)
	{
		delete m_apModel;
		m_apModel = NULL;
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
		}
		else
		{
			return;
		}
	}

	//���n��Ԃ��擾
	m_bRand = CManager::GetMesh()->OnMesh(m_pos);

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
		CManager::GetDebugProc()->Print("\n\n\n�O�ɏo�Ă���\n");
	}

	//�ړ��ʂ̓K�p
	m_pos += m_move;

	//��]����
	Rotate();

	//�G�t�F�N�g���Ăяo��
	CEffect::Create(m_pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), m_rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100);

	m_apModel[0]->SetTransform(m_pos, m_rot);

	//�e�̏����X�V����
	m_pShadow->SetTransform(m_pos, m_rot);
	
	//���S����
	if (m_pos.y < -500.0f)
	{
		m_nLife--;
		m_bDead = true;
	}

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("\n\n\n�v���C���[���W : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
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

	//������
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, size, rot);
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
//  �v���C���[���̓ǂݍ���
//==========================================
void CPlayer::Load(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����
	char aStr[256]; //�s�v�ȕ�����̋L�^�p

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(TXTFILENAME_PLAYER, "r");

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
