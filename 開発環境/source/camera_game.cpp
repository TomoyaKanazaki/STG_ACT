//==========================================
//
//  �J�����Q�[���N���X(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraGame::CCameraGame()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraGame::~CCameraGame()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraGame::Init(void)
{
	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraGame::Update(void)
{
	//���_����
	ThirdPerson();

	CCamera::Update();
}

//==========================================
//  ��l�̎��_�̑���
//==========================================
void CCameraGame::FirstPerson(void)
{
	//���_�̒l���X�V
	m_rot += CManager::GetMouse()->GetMouseMove();

	//�p�x�̕␳
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//�p�x���X�V
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.x)) * CAMERA_DISTANCE;
	m_posR.y = m_posV.y - cosf(m_rot.z) * CAMERA_DISTANCE;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * CAMERA_DISTANCE;
}

//==========================================
//  �O�l�̎��_�̑���
//==========================================
void CCameraGame::ThirdPerson(void)
{
	//�����_���X�V
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//���_�̒l���X�V
	m_rot.y += CManager::GetMouse()->GetMouseMove().x;

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//���_���X�V
	m_posV.x = posPlayer.x + (sinf(m_rot.y) * CAMERA_DISTANCE);
	m_posV.y = posPlayer.y + HEIGHT;
	m_posV.z = posPlayer.z + (cosf(m_rot.y) * CAMERA_DISTANCE);

	//�����_���X�V
	m_posR.x = posPlayer.x - (sinf(m_rot.y) * CAMERA_DISTANCE);
	m_posR.y = posPlayer.y;
	m_posR.z = posPlayer.z - (cosf(m_rot.y) * CAMERA_DISTANCE);
}

//==========================================
//  �ړ�
//==========================================
void CCameraGame::Move(void)
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�ɃJ������Ǐ]������
	m_posV = pos;
	m_posR = pos;

	//�v���C���[����J�����𗣂�
	m_posV += m_diff;
	m_posR -= m_diff;
	m_posR.y = pos.y;
}
