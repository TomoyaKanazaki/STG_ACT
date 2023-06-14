//==========================================
//
//  �I�u�W�F�N�g3D�N���X(object3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object3D.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bBillboard = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject3D::~CObject3D()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�l��ۑ�����
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	//���[�J���ϐ��錾
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.z * m_size.z) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.z);

	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (GetType() == TYPE_FIELD)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//���_�J���[�̐ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

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
void CObject3D::Uninit(void)
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
void CObject3D::Update(void)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (GetType() == TYPE_FIELD)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//���_�J���[�̐ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �`�揈��
//==========================================
void CObject3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans, mtxView; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���{�[�h�����
	if (m_bBillboard)
	{
		//�r���[�}�g���b�N�X�̎擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

		//�l�̕␳
		m_mtxWorld._41 = m_pos.x;
		m_mtxWorld._42 = m_pos.y;
		m_mtxWorld._43 = m_pos.z;
	}
	else
	{
		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==========================================
//  �e�N�X�`�����W�̕ύX
//==========================================
void CObject3D::SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max)
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
void CObject3D::SetCol(const D3DXCOLOR col)
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
