//==========================================
//
//  �I�u�W�F�N�g2D�N���X(object2D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject2D::~CObject2D()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�l��ۑ�����
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	//���[�J���ϐ��錾
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		0.0f
	);
	pVtx[1].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	);
	pVtx[2].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	);
	pVtx[3].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle)) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle)) * m_fLength,
		0.0f
	);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CObject2D::Update(void)
{
	//�Ίp�� / 2�̌v�Z
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		0.0f
	);
	pVtx[1].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	);
	pVtx[2].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	);
	pVtx[3].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle)) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle)) * m_fLength,
		0.0f
	);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �`�揈��
//==========================================
void CObject2D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==========================================
//  �e�N�X�`�����W�̕ύX
//==========================================
void CObject2D::SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(min.x, min.y);
	pVtx[1].tex = D3DXVECTOR2(max.x, min.y);
	pVtx[2].tex = D3DXVECTOR2(min.x, max.y);
	pVtx[3].tex = D3DXVECTOR2(max.x, max.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �F�̐ݒ�
//==========================================
void CObject2D::SetCol(const D3DXCOLOR col)
{
	//�F��ݒ肷��
	m_col = col;

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ݒ肵���F�̓K�p
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
