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
#include "bullet.h"
#include "effect.h"

//==========================================
//  �}�N����`
//==========================================
#define MOUSE_SPEED (0.03f) //�v���C���[�̈ړ����x(�}�E�X)
#define KEYBOARD_SPEED (1.0f) //�v���C���[�̈ړ����x(�L�[�{�[�h)

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSpeed = 0.0f;
	m_fRotMove = 0.0f;
	m_fRotDest = 0.0f;
	m_fRotDiff = 0.0f;
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
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_PLAYER);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	//�ړ�����
	Move();

	//��]����
	Rotate();

	if (CManager::GetMouse()->GetTrigger(CMouse::BUTTON_LEFT) || CManager::GetKeyboard()->GetPress(DIK_SPACE))
	{
		CBullet::Create(m_pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), m_rot);
	}

	//�X�V����
	CObject2D::Update();

	//�G�t�F�N�g���Ăяo��
	CEffect::Create(m_pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), m_rot, D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f),  30);
}

//==========================================
//  �`�揈��
//==========================================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  �e�N�X�`���̓ǂݍ���
//==========================================
HRESULT CPlayer::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/Player.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �e�N�X�`���̔j��
//==========================================
void CPlayer::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
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

	//�e�N�X�`�������蓖�Ă�
	pPlayer->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pPlayer;
}

//==========================================
//  �ړ�����
//==========================================
void CPlayer::Move(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 move = CManager::GetKeyboard()->GetWASD();
	D3DXVECTOR3 mouse = CManager::GetMouse()->GetMouseMove();

	//�ړ��ʂ̎擾
	if (move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_move.x += mouse.x * MOUSE_SPEED;
		m_move.y += mouse.y * MOUSE_SPEED;
	}
	else
	{
		m_move.x += move.x * KEYBOARD_SPEED;
		m_move.y += move.y * KEYBOARD_SPEED;
	}
	m_pos += m_move;

	//x�����̈ړ�����
	if (m_pos.x + (m_size.x * 0.5f) > SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - (m_size.x * 0.5f);
	}
	if (m_pos.x - (m_size.x * 0.5f) < 0.0f)
	{
		m_pos.x = (m_size.x * 0.5f);
	}

	//y�����̈ړ�����
	if (m_pos.y + (m_size.y * 0.5f) > SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - (m_size.y * 0.5f);
	}
	if (m_pos.y - (m_size.y * 0.5f) < 0.0f)
	{
		m_pos.y = (m_size.y * 0.5f);
	}

	//�������ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
}

//==========================================
//  ��]����
//==========================================
void CPlayer::Rotate(void)
{
	//�ڕW�p�x�̎擾
	if (m_move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_fRotDest = -atan2f(m_move.x, -m_move.y);
	}

	//���݊p�x�̎擾
	m_fRotMove = m_rot.z;

	//�ڕW-���݊p�x�̍������擾
	m_fRotDiff = m_fRotDest - m_fRotMove;

	//�����̒l��␳
	if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
	{
		if (m_fRotDiff > D3DX_PI)
		{
			m_fRotDiff += (-D3DX_PI * 2);
		}
		else if (m_fRotDiff <= -D3DX_PI)
		{
			m_fRotDiff += (D3DX_PI * 2);
		}
	}

	//��]����
	m_rot.z += m_fRotDiff * 0.2f;

	//��]�p�x�̕␳
	if (m_rot.z > D3DX_PI || m_rot.z < -D3DX_PI)
	{
		if (m_rot.z > D3DX_PI)
		{
			m_rot.z += (-D3DX_PI * 2);
		}
		else if (m_rot.z < -D3DX_PI)
		{
			m_rot.z += (D3DX_PI * 2);
		}
	}
}
