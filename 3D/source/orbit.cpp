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
	m_pVtxBuff = NULL;
	m_nLife = 0;
	m_nNumVtx = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_offset[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_offset[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_offset[nCnt].mtxWorld = {};
	}
	m_mtxWorld = {};
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
	//�l�̎Z�o
	m_nNumVtx = m_nLife * 2;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�I�t�Z�b�g�̈ʒu���Z�o
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//���[�J���ϐ��錾
		D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent; //�e�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_offset[nCnt].mtxWorld);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_offset[nCnt].mtxWorld, &m_offset[nCnt].mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, m_offset[nCnt].pos.x, m_offset[nCnt].pos.y, m_offset[nCnt].pos.z);
		D3DXMatrixMultiply(&m_offset[nCnt].mtxWorld, &m_offset[nCnt].mtxWorld, &mtxTrans);

		//�e�}�g���b�N�X�̐ݒ�
		mtxParent = m_parent->GetMtx();

		//���[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
		D3DXMatrixMultiply
		(
			&m_offset[nCnt].mtxWorld,
			&m_offset[nCnt].mtxWorld,
			&mtxParent
		);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_offset[nCnt].mtxWorld);
	}

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
			pVtx[nCntVtx].pos = D3DXVECTOR3(m_offset[0].mtxWorld._41, m_offset[0].mtxWorld._42, m_offset[0].mtxWorld._43);

			//�@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = m_colDef;

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
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�I�t�Z�b�g�̈ʒu���Z�o
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//���[�J���ϐ��錾
		D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent; //�e�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_offset[nCnt].mtxWorld);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_offset[nCnt].mtxWorld, &m_offset[nCnt].mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, m_offset[nCnt].pos.x, m_offset[nCnt].pos.y, m_offset[nCnt].pos.z);
		D3DXMatrixMultiply(&m_offset[nCnt].mtxWorld, &m_offset[nCnt].mtxWorld, &mtxTrans);

		//�e�}�g���b�N�X�̐ݒ�
		mtxParent = m_parent->GetMtx();

		//���[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
		D3DXMatrixMultiply
		(
			&m_offset[nCnt].mtxWorld,
			&m_offset[nCnt].mtxWorld,
			&mtxParent
		);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_offset[nCnt].mtxWorld);
	}

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ꎞ�ۑ��p�ϐ�
	D3DXVECTOR3 *oldpos = new D3DXVECTOR3[m_nNumVtx];
	D3DXCOLOR *oldcol = new D3DXCOLOR[m_nNumVtx];

	//�O�����ۑ�����
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		oldpos[nCnt] = pVtx[nCnt].pos;
		oldcol[nCnt] = pVtx[nCnt].col;
	}

	//���_�������炷
	for (int nCnt = 2; nCnt < m_nNumVtx; nCnt++)
	{
		pVtx[nCnt].pos = oldpos[nCnt - 2];
		pVtx[nCnt].col = oldcol[nCnt - 2];
	}

	//���������J��
	delete[] oldpos;
	delete[] oldcol;

	//�ŐV�̏���ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_offset[0].mtxWorld._41, m_offset[0].mtxWorld._42, m_offset[0].mtxWorld._43);
	pVtx[0].col = m_offset[0].col;
	pVtx[1].pos = D3DXVECTOR3(m_offset[1].mtxWorld._41, m_offset[1].mtxWorld._42, m_offset[1].mtxWorld._43);
	pVtx[1].col = m_offset[1].col;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		CManager::GetDebugProc()->Print("�O�Ս��W : ( %f, %f, %f )\n", pVtx[nCnt].pos.x, pVtx[nCnt].pos.y, pVtx[nCnt].pos.z);
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �`�揈��
//==========================================
void COrbit::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�����O�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�}�g���b�N�X�̐ݒ�
	D3DXMATRIX mtxParent = m_parent->GetMtx();

	//���[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
	D3DXMatrixMultiply
	(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent
	);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);

	//�J�����O��L����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
COrbit *COrbit::Create(CModel *pParent, D3DXCOLOR col, D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, int nLife)
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
	pOrbit->m_colDef = col;
	pOrbit->m_offset[0].pos = offset0;
	pOrbit->m_offset[1].pos = offset1;
	pOrbit->m_nLife = nLife;

	//������
	pOrbit->Init();

	//�|�C���^��Ԃ�
	return pOrbit;
}
