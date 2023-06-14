//==========================================
//
//  �v���C���[�N���X(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "object_x.h"
#include "camera.h"

//==========================================
//  �}�N����`
//==========================================
#define PLAYER_SPEED (1.0f) //�v���C���[�̈ړ����x(�L�[�{�[�h)

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 0.0f;
	m_fAngle = 0.0f;
	body = NULL;
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

	//���f���𐶐�����
	body = CObject_X::Create(m_pos, m_size, m_rot);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CPlayer::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	//�O����W�̕ۑ�
	D3DXVECTOR3 oldpos = m_pos;

	//�ړ�����
	Move();

	//��]����
	if (oldpos != m_pos)
	{
		Rotate();
	}

	//���f���ɏ���^����
	body->SetTransform(m_pos, m_rot);

	//�G�t�F�N�g���Ăяo��
	CEffect::Create(m_pos, D3DXVECTOR3(30.0f, 0.0f, 30.0f), m_rot, D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f), 30);

	CManager::GetDebugProc()->Print("\n\n\n�v���C���[���W : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("�v���C���[���� : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("�v���C���[�ړ��� : ( %f, %f, %f )\n", m_move.x, m_move.y, m_move.z);
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

	//�ړ������̎擾
	m_fAngle = atan2f(m_move.x, m_move.z);

	//�ړ��ʂ̓K��
	m_pos += m_move;
}

//==========================================
//  ��]����
//==========================================
void CPlayer::Rotate(void)
{
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
	fRotMove += fRotDiff * 0.2f;

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

	m_fAngle = m_rot.y;
}
