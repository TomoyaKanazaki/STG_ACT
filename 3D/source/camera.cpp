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

//==========================================
//  �}�N����`
//==========================================
#define DISTANCE (200.0f) //���_�ƒ����_�̋���
#define SPEED (0.05f) //�J�����̃X�s�[�h
#define MAX_ROT (D3DX_PI * 0.99f) //���_�̌��E�p
#define MIN_ROT (D3DX_PI * 0.01f) //���_�̌��E�p

//==========================================
//  �R���X�g���N�^
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 150.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z), 0.0f, tanf(m_posR.y - m_posV.y));
	m_rot.x = (D3DX_PI * 0.5f);

	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.x)) * DISTANCE;
	m_posV.y = m_posR.y + cosf(m_rot.z) * DISTANCE;
	m_posV.z = m_posR.z + (sinf(m_rot.z) * sinf(m_rot.x)) * DISTANCE;

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
	if (CManager::GetMouse()->GetPress(CMouse::BUTTON_LEFT) && CManager::GetMouse()->GetPress(CMouse::BUTTON_RIGHT))
	{
		Move();
	}
	else if (CManager::GetMouse()->GetPress(CMouse::BUTTON_LEFT))
	{
		ThirdPerson();
	}
	else if (CManager::GetMouse()->GetPress(CMouse::BUTTON_RIGHT))
	{
		FirstPerson();
	}
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
		D3DXToRadian(54.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f
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
