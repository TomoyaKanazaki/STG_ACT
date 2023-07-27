//==========================================
//
//  �J�����N���X(camera.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "target.h"
#include "gamemanager.h"

//==========================================
//  �}�N����`
//==========================================
#define DISTANCE (1000.0f) //���_�ƒ����_�̋���
#define DISTANCE_LEVEL (0.4f) //xz�̊���
#define SPEED (0.05f) //�J�����̃X�s�[�h
#define MAX_ROT (D3DX_PI * 0.99f) //���_�̌��E�p
#define MIN_ROT (D3DX_PI * 0.01f) //���_�̌��E�p
#define FOV_MIN (45.0f) //����p�̍Œ�l
#define FOV_MAX (54.0f) //����p�̍ő�l

//==========================================
//  �R���X�g���N�^
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 150.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FOV = FOV_MIN;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCamera::~CCamera()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCamera::Init(void)
{
	//������x�N�g����ݒ�
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�ʒu��ݒ�
	CalcPos(SLIP_OFF);

	//�^�[�Q�b�g�𐶐�
	CTarget::Create(D3DXVECTOR3(30.0f, 0.0f, 30.0f));

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CCamera::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CCamera::Update(void)
{
	//�ʒu�̍X�V
	CalcPos(SLIP_ON);
	//ThirdPerson();

	//����p�̍X�V
	CalcFOV();

	CManager::GetDebugProc()->Print("�����_ : ( %f, %f, %f )\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetDebugProc()->Print("���_ : ( %f, %f, %f )\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetDebugProc()->Print("�p�x : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);
}

//==========================================
//  �ݒ菈��
//==========================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(m_FOV),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f
	);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH
	(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==========================================
//  ��l�̎��_�̑���
//==========================================
void CCamera::FirstPerson(void)
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
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.x)) * DISTANCE;
	m_posR.y = m_posV.y - cosf(m_rot.z) * DISTANCE;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * DISTANCE;
}

//==========================================
//  �O�l�̎��_�̑���
//==========================================
void CCamera::ThirdPerson(void)
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
	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.x)) * DISTANCE;
	m_posV.y = m_posR.y + cosf(m_rot.z) * DISTANCE;
	m_posV.z = m_posR.z + (sinf(m_rot.z) * sinf(m_rot.x)) * DISTANCE;
}

//==========================================
//  �ړ�
//==========================================
void CCamera::Move(void)
{
	//�}�E�X
	m_posR += CManager::GetMouse()->GetMouseMove();
	m_posV += CManager::GetMouse()->GetMouseMove();

	//�L�[�{�[�h
	if (CManager::GetKeyboard()->GetPress(DIK_Q))
	{
		m_rot.x -= 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		m_rot.x += 0.01f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_R))
	{
		m_rot.y += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_V))
	{
		m_rot.y -= 0.01f;
	}
}

//==========================================
//  �J�����ʒu�v�Z����
//==========================================
void CCamera::CalcPos(SLIP slipFlag)
{
	m_posR = CGameManager::GetPlayer()->GetPos();
	m_rot.x = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);
	m_rot.z = tanf(m_posR.y - m_posV.y);

	//�ړ��ʂ��擾
	D3DXVECTOR3 rot = CGameManager::GetPlayer()->GetRot();

	if (slipFlag == SLIP_ON)
	{
		float fRotMove, fRotDest, fRotDiff;

		//���݂̊p�x�ƖړI�̊p�x�̍������v�Z
		fRotMove = m_rot.y;
		fRotDest = rot.y;
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
		fRotMove += fRotDiff * 0.03f;

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
	else
	{
		m_rot = rot;
	}

	//�����_�̂����ݒ�
	D3DXVECTOR3 slip = D3DXVECTOR3(sinf(m_rot.y) * -100.0f, 0.0f, cosf(m_rot.y) * -100.0f);

	m_posR += slip;
	m_posV = D3DXVECTOR3(m_posR.x, DISTANCE, m_posR.z - DISTANCE * DISTANCE_LEVEL);
}

//==========================================
//  ����p�̌v�Z
//==========================================
void CCamera::CalcFOV(void)
{
	//���[�J���ϐ��錾
	float fDeff = FOV_MIN;

	//�ꍇ����
	switch (CGameManager::GetState())
	{
	case CGameManager::SHOT:
		fDeff = FOV_MIN;
		break;
	case CGameManager::BLADE:
		fDeff = FOV_MAX;
		break;
	}

	//�ڕW�̎���p�܂Ŋg�k����
	m_FOV += (fDeff - m_FOV) * 0.08f;
}
