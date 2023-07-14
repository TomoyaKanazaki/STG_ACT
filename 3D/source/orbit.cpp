//==========================================
//
//  �O�ՃN���X(orbit.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "orbit.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "debugproc.h"

//==========================================
//  �R���X�g���N�^
//==========================================
COrbit::COrbit()
{
	m_parent = NULL;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_nLife = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
COrbit::~COrbit()
{

}

//==========================================
//  ����������
//==========================================
HRESULT COrbit::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_nLife > 0)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer
		(
			sizeof(VERTEX_3D) * m_nNumVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL
		);

		//���_�o�b�t�@�̌Ăяo��
		VERTEX_3D *pVtx;

		//���_�o�b�t�@�̃��b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_����������
		for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
		{
			//���_���W�̐ݒ�
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = m_Col;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void COrbit::Uninit(void)
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
void COrbit::Update(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 *pOldPos = new D3DXVECTOR3[m_nNumVtx - 2];

	//�e�̎擾
	D3DXMATRIX mtxWorld, mtxRot, mtxTrans;
	m_rot = m_parent->GetRot();
	m_pos = m_parent->GetPos();

	////���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&m_mtxWorld);

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	////�ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�O��ʒu��ۑ�
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx - 2; nCntVtx++)
	{
		pOldPos[nCntVtx] = pVtx[nCntVtx].pos;
	}

	//�ŐV�̒��_�ʒu��ݒ�
	pVtx[0].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.y) * m_fLength,
		m_pos.y,
		m_pos.z + cosf(m_rot.y) * m_fLength
	);
	pVtx[1].pos = m_pos;

	//���_���W�����炷
	for (int nCntVtx = 2; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		pVtx[nCntVtx].pos = pOldPos[nCntVtx - 2];
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//���������J��
	delete[] pOldPos;
}

//==========================================
//  �`�揈��
//==========================================
void COrbit::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�J�����O�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,
		0,
		m_nNumVtx - 2
	);

	//�J�����O��L����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
COrbit *COrbit::Create(CModel *pParent, D3DXCOLOR col, float fLength, int nLife)
{
	//�C���X�^���X����
	COrbit *pOrbit = NULL;

	//NULL�`�F�b�N
	if (pOrbit == NULL)
	{
		//���������m��
		pOrbit = new COrbit;
	}

	if (pOrbit == NULL)
	{
		return NULL;
	}

	//�l��ݒ�
	pOrbit->m_parent = pParent;
	pOrbit->m_Col = col;
	pOrbit->m_fLength = fLength;
	pOrbit->m_nLife = nLife;
	pOrbit->m_nNumVtx = pOrbit->m_nLife * 2;

	//������
	pOrbit->Init();

	//�|�C���^��Ԃ�
	return pOrbit;
}
