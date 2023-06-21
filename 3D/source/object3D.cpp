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

	if (GetType() == TYPE_FIELD || GetType() == TYPE_SHADOW)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);
	}

	D3DXVECTOR3 nor0;
	D3DXVECTOR3 nor1;
	D3DXVECTOR3 nor2;
	D3DXVECTOR3 nor3;

	//0
	D3DXVECTOR3 vecLine01 = pVtx[1].pos - pVtx[0].pos;
	D3DXVECTOR3 vecLine02 = pVtx[2].pos - pVtx[0].pos;

	D3DXVec3Cross(&nor0, &vecLine01, &vecLine02);
	D3DXVec3Normalize(&nor0, &nor0);

	//1
	D3DXVECTOR3 vecLine10 = pVtx[0].pos - pVtx[1].pos;
	D3DXVECTOR3 vecLine13 = pVtx[3].pos - pVtx[1].pos;

	D3DXVec3Cross(&nor1, &vecLine10, &vecLine13);
	D3DXVec3Normalize(&nor1, &nor1);

	//2
	D3DXVECTOR3 vecLine20 = pVtx[0].pos - pVtx[2].pos;
	D3DXVECTOR3 vecLine23 = pVtx[3].pos - pVtx[2].pos;

	D3DXVec3Cross(&nor2, &vecLine20, &vecLine23);
	D3DXVec3Normalize(&nor2, &nor2);

	//3
	D3DXVECTOR3 vecLine31 = pVtx[1].pos - pVtx[3].pos;
	D3DXVECTOR3 vecLine32 = pVtx[2].pos - pVtx[3].pos;

	D3DXVec3Cross(&nor3, &vecLine31, &vecLine32);
	D3DXVec3Normalize(&nor3, &nor3);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = nor0;
	pVtx[1].nor = nor1;
	pVtx[2].nor = nor2;
	pVtx[3].nor = nor3;

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

	if (GetType() == TYPE_FIELD || GetType() == TYPE_SHADOW)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);
	}
	else
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);
	}

	D3DXVECTOR3 nor0;
	D3DXVECTOR3 nor1;
	D3DXVECTOR3 nor2;
	D3DXVECTOR3 nor3;

	//0
	D3DXVECTOR3 vecLine01 = pVtx[1].pos - pVtx[0].pos;
	D3DXVECTOR3 vecLine02 = pVtx[2].pos - pVtx[0].pos;

	D3DXVec3Cross(&nor0, &vecLine01, &vecLine02);
	D3DXVec3Normalize(&nor0, &nor0);

	//1
	D3DXVECTOR3 vecLine10 = pVtx[0].pos - pVtx[1].pos;
	D3DXVECTOR3 vecLine13 = pVtx[3].pos - pVtx[1].pos;

	D3DXVec3Cross(&nor1, &vecLine10, &vecLine13);
	D3DXVec3Normalize(&nor1, &nor1);

	//2
	D3DXVECTOR3 vecLine20 = pVtx[0].pos - pVtx[2].pos;
	D3DXVECTOR3 vecLine23 = pVtx[3].pos - pVtx[2].pos;

	D3DXVec3Cross(&nor2, &vecLine20, &vecLine23);
	D3DXVec3Normalize(&nor2, &nor2);

	//3
	D3DXVECTOR3 vecLine31 = pVtx[1].pos - pVtx[3].pos;
	D3DXVECTOR3 vecLine32 = pVtx[2].pos - pVtx[3].pos;

	D3DXVec3Cross(&nor3, &vecLine31, &vecLine32);
	D3DXVec3Normalize(&nor3, &nor3);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = nor0;
	pVtx[1].nor = nor1;
	pVtx[2].nor = nor2;
	pVtx[3].nor = nor3;

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
	VERTEX_3D *pVtx;

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
	VERTEX_3D *pVtx;

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

//==========================================
//  �������擾���鏈��
//==========================================
float CObject3D::GetHeight(const D3DXVECTOR3 TargetPos)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 VtxPos[4]; //���_�̈ʒu��ۑ�����
	D3DXVECTOR3 NorPlane[2]; //�ΏۂɂȂ�@��
	float fHeight = 0.0f; //�Ԃ�l

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̒��_���擾
	VtxPos[0] = pVtx[0].pos;
	VtxPos[1] = pVtx[1].pos;
	VtxPos[2] = pVtx[2].pos;
	VtxPos[3] = pVtx[3].pos;

	//�@�����擾
	NorPlane[0] = pVtx[0].nor;
	NorPlane[1] = pVtx[3].nor;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	if
		(
			((VtxPos[1].z - VtxPos[0].z) * (TargetPos.x - VtxPos[0].x)) - ((VtxPos[1].x - VtxPos[0].x) * (TargetPos.z - VtxPos[0].z)) > 0.0f &&
			((VtxPos[2].z - VtxPos[1].z) * (TargetPos.x - VtxPos[1].x)) - ((VtxPos[2].x - VtxPos[1].x) * (TargetPos.z - VtxPos[1].z)) > 0.0f &&
			((VtxPos[0].z - VtxPos[2].z) * (TargetPos.x - VtxPos[2].x)) - ((VtxPos[0].x - VtxPos[2].x) * (TargetPos.z - VtxPos[2].z)) > 0.0f
		)
	{
		//�@���������łȂ��ꍇ
		if (NorPlane[0].y != 0.0f)
		{
			fHeight = (-(TargetPos.x * NorPlane[0].x + TargetPos.z * NorPlane[0].z) + (VtxPos[0].x * NorPlane[0].x + VtxPos[0].y * NorPlane[0].y + VtxPos[0].z * NorPlane[0].z)) / NorPlane[0].y;
		}
	}

	if
		(
			((VtxPos[2].z - VtxPos[3].z) * (TargetPos.x - VtxPos[3].x)) - ((VtxPos[2].x - VtxPos[3].x) * (TargetPos.z - VtxPos[3].z)) > 0.0f &&
			((VtxPos[1].z - VtxPos[2].z) * (TargetPos.x - VtxPos[2].x)) - ((VtxPos[1].x - VtxPos[2].x) * (TargetPos.z - VtxPos[2].z)) > 0.0f &&
			((VtxPos[3].z - VtxPos[1].z) * (TargetPos.x - VtxPos[1].x)) - ((VtxPos[3].x - VtxPos[1].x) * (TargetPos.z - VtxPos[1].z)) > 0.0f
		)
	{
		//�@���������łȂ��ꍇ
		if (NorPlane[1].y != 0.0f)
		{
			fHeight = (-(TargetPos.x * NorPlane[1].x + TargetPos.z * NorPlane[1].z) + (VtxPos[3].x * NorPlane[1].x + VtxPos[3].y * NorPlane[1].y + VtxPos[3].z * NorPlane[1].z)) / NorPlane[1].y;
		}
	}

	return fHeight;
}
