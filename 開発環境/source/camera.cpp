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
#include "gamemanager.h"

//==========================================
//  �}�N����`
//==========================================
#define DISTANCE_V (500.0f) //���_����v���C���[�̋���
#define DISTANCE_R (5.0f) //�v���C���[���璍���_�̔{��
#define HEIGHT (500.0f) //���_�̍���
#define MAX_ROT (D3DX_PI * 0.99f) //���_�̌��E�p
#define MIN_ROT (D3DX_PI * 0.01f) //���_�̌��E�p

//==========================================
//  �R���X�g���N�^
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, HEIGHT, DISTANCE_V);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, -DISTANCE_V);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_diff = D3DXVECTOR3(0.0f, HEIGHT, DISTANCE_V);
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
		20000.0f
	);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X���v�Z
	CreateViewMatrix();

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
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.x)) * DISTANCE_V;
	m_posR.y = m_posV.y - cosf(m_rot.z) * DISTANCE_V;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * DISTANCE_V;
}

//==========================================
//  �O�l�̎��_�̑���
//==========================================
void CCamera::ThirdPerson(void)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPos = CGameManager::GetPlayer()->GetPos();
	PlayerPos.y += HEIGHT;

	//���_�̒l���X�V
	if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		m_rot += CManager::GetMouse()->GetMouseMove();
	}

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

	//���_���X�V
	m_posV.x = PlayerPos.x + (sinf(m_rot.z) * cosf(m_rot.x)) * DISTANCE_V;
	m_posV.y = PlayerPos.y + cosf(m_rot.z) * DISTANCE_V;
	m_posV.z = PlayerPos.z + (sinf(m_rot.z) * sinf(m_rot.x)) * -DISTANCE_V;

	////�����_���X�V
	m_posR = PlayerPos - (m_posV * DISTANCE_R);

	//�p�x���X�V
	m_rot.y = atan2f(m_posR.x, m_posR.z);
}

//==========================================
//  �ړ�
//==========================================
void CCamera::Move(void)
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�ɃJ������Ǐ]������
	m_posV = pos;
	m_posR = pos;

	//�J�����̈ړ�
	if (CManager::GetKeyboard()->GetPress(DIK_Z))
	{
		m_diff.x -= 3.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_C))
	{
		m_diff.x += 3.0f;
	}

	//�v���C���[����J�����𗣂�
	m_posV += m_diff;
	m_posR -= m_diff;
	m_posR.y = pos.y;
}

//==========================================
//  ��]����
//==========================================
void CCamera::Rotate(void)
{
	//���_���璍���_�ւ̃x�N�g�������߂�
	D3DXVECTOR3 vecCamera = m_posR - m_posV;

	//���߂��x�N�g������p�x�����߂�
	m_rot.x = atan2f(vecCamera.y, vecCamera.z);
	m_rot.y = atan2f(vecCamera.z, vecCamera.x);
	m_rot.z = atan2f(vecCamera.x, vecCamera.y);
}

//==========================================
//  �r���[�}�g���b�N�X�̐���
//==========================================
D3DXMATRIX CCamera::CreateViewMatrix(void)
{
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

	return m_mtxView;
}
