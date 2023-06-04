//==========================================
//
//  �G�l�~�[�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "object.h"

//==========================================
//  �}�N����`
//==========================================
#define ENEMY_SPEED (5.0f) //�G�l�~�[�̈ړ����x

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
int CEnemy::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy()
{
	m_move = D3DXVECTOR3((float)(rand() % 100), (float)(rand() % 100), 0.0f);
	if (rand() % 2)
	{
		m_move.x *= -1.0f;
	}
	if (rand() % 2)
	{
		m_move.y *= -1.0f;
	}

	m_nSpeed = ENEMY_SPEED;
	m_fRotMove = 0.0f;
	m_fRotDest = 0.0f;
	m_fRotDiff = 0.0f;

	m_nNum++;
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
HRESULT CEnemy::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();

	m_nNum--;
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	//�ړ�����
	Move();
	
	//��]����
	Rotate();

	//�X�V����
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  �e�N�X�`���̓ǂݍ���
//==========================================
HRESULT CEnemy::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/Enemy_0.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �e�N�X�`���̔j��
//==========================================
void CEnemy::UnLoad(void)
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
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CEnemy *pEnemy = NULL;

	//NULL�`�F�b�N
	if (pEnemy == NULL)
	{
		//���������m��
		pEnemy = new CEnemy;
	}

	//������
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	pEnemy->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pEnemy;
}

//==========================================
//  �ړ�����
//==========================================
void CEnemy::Move(void)
{
	//x�����̈ړ�����
	if (m_pos.x + (m_size.x * 0.5f) > SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - (m_size.x * 0.5f);
		m_move.x *= -1.0f;
	}
	if (m_pos.x - (m_size.x * 0.5f) < 0.0f)
	{
		m_pos.x = (m_size.x * 0.5f);
		m_move.x *= -1.0f;
	}

	//y�����̈ړ�����
	if (m_pos.y + (m_size.y * 0.5f) > SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - (m_size.y * 0.5f);
		m_move.y *= -1.0f;
	}
	if (m_pos.y - (m_size.y * 0.5f) < 0.0f)
	{
		m_pos.y = (m_size.y * 0.5f);
		m_move.y *= -1.0f;
	}

	//���K��
	D3DXVec3Normalize(&m_move, &m_move);
	m_move.x *= m_nSpeed;
	m_move.y *= m_nSpeed;

	//�G���m�̓����蔻��
	Collision();

	//�ړ�����
	m_pos += m_move;
}

//==========================================
//  ��]����
//==========================================
void CEnemy::Rotate(void)
{
	//���݊p�x�̎擾
	m_fRotMove = m_rot.z;
	m_fRotDest = m_rot.z + 0.2f;

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

//==========================================
//  �G���m�̓����蔻��
//==========================================
void CEnemy::Collision(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (nCntObj != GetID())
		{
			//�C���X�^���X����
			CObject *pObj;

			//�I�u�W�F�N�g���擾
			pObj = GetObject(nCntObj);

			//NULL�`�F�b�N
			if (pObj != NULL)
			{
				//��ނ̎擾
				TYPE type = pObj->GetType();

				if (type == TYPE_ENEMY) //�G�̏ꍇ
				{
					//�G�̊e�����擾����
					D3DXVECTOR3 pos = pObj->GetPos();
					D3DXVECTOR3 size = pObj->GetSize();

					//�G�ƒe�̋������擾
					float fLength = (pos.x - m_pos.x) * (pos.x - m_pos.x) + (pos.y - m_pos.y) * (pos.y - m_pos.y);

					//���苗�����擾
					float fOutLine = (size.x - m_size.x * 0.3f) * (size.x - m_size.x * 0.3f) + (size.y - m_size.y * 0.3f) * (size.y - m_size.y * 0.3f);

					if (fLength < fOutLine)
					{
						m_move.x *= -1.0f;
						m_move.y *= -1.0f;
					}
				}
			}
		}
	}
}