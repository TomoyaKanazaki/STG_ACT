//==========================================
//
//  ���b�V���I�u�W�F�N�g�N���X(object_mesh.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_mesh.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CObject_Mesh::CObject_Mesh(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_Mesh.nNumIdx = 0;
	m_Mesh.nNumMesh = 0;
	m_Mesh.nNumMesh_U = 0;
	m_Mesh.nNumMesh_V = 0;
	m_Mesh.nNumVtx = 0;
	m_Mesh.nNumVtx_U = 0;
	m_Mesh.nNumVtx_V = 0;
	m_mtxWorld = {};
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject_Mesh::~CObject_Mesh()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject_Mesh::Init(void)
{
	//���_�����p�ϐ��̐ݒ�
	CalcData();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * m_Mesh.nNumMesh,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	//���_�o�b�t�@�̏���ݒ�
	SetVtx();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * m_Mesh.nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL
	);

	//�C���f�b�N�X�o�b�t�@�̏���ݒ�
	SetIdx();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject_Mesh::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CObject_Mesh::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CObject_Mesh::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C���[�t���[����L����
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_Mesh.nNumVtx, //���_��
		0,
		m_Mesh.nNumMesh //�v���~�e�B�u��
	);

	//���C���[�t���[���𖳌���
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CObject_Mesh * CObject_Mesh::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv)
{
	//�C���X�^���X����
	CObject_Mesh *pMesh = NULL;

	//NULL�`�F�b�N
	if (pMesh == NULL)
	{
		//���������m��
		pMesh = new CObject_Mesh;
	}

	if (pMesh == NULL)
	{
		return NULL;
	}

	//��������ݒ�
	pMesh->m_Mesh.nNumMesh_U = (int)uv.x;
	pMesh->m_Mesh.nNumMesh_V = (int)uv.y;
	pMesh->m_pos = pos;
	pMesh->m_size = size;
	pMesh->m_rot = rot;

	//������
	pMesh->Init();

	//�e�N�X�`�������蓖�Ă�
	pMesh->BindTexture(CManager::GetTexture()->GetAddress(0));

	//�|�C���^��Ԃ�
	return pMesh;
}

//==========================================
//  ���_�o�b�t�@�̐ݒ菈��
//==========================================
void CObject_Mesh::SetVtx(void)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_Mesh.nNumVtx; nCntVtx++)
	{
		//�@���̐ݒ�
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
	}	

	//���_���W�̐ݒ�
	for (int nCntVtxU = 0; nCntVtxU < m_Mesh.nNumVtx_U; nCntVtxU++)
	{
		for (int nCntVtxV = 0; nCntVtxV < m_Mesh.nNumVtx_V; nCntVtxV++)
		{
			pVtx[nCntVtxU + (nCntVtxV * m_Mesh.nNumVtx_U)].pos = D3DXVECTOR3
			(
				-(m_size.x * 0.5f) + ((m_size.x / m_Mesh.nNumMesh_U) * nCntVtxU),
				0.0f,
				(m_size.z * 0.5f) - ((m_size.z / m_Mesh.nNumMesh_V) * nCntVtxV)
			);
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �C���f�b�N�X�o�b�t�@�̐ݒ菈��
//==========================================
void CObject_Mesh::SetIdx(void)
{
	//�C���f�b�N�X���ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�f�[�^�̐ݒ�
	for (int nCntIdx = 0, nCntTurn = 0, nCntVtx = 0; nCntIdx < m_Mesh.nNumIdx; nCntIdx += 2)
	{
		if (nCntIdx == (2 * ((m_Mesh.nNumVtx_U * nCntTurn) + m_Mesh.nNumVtx_U + nCntTurn))) //�܂�Ԃ��n�_
		{
			pIdx[nCntIdx] = pIdx[nCntIdx - 1];
			pIdx[nCntIdx + 1] = nCntVtx + m_Mesh.nNumVtx_U;
			nCntTurn++;
		}
		else //���̑�
		{
			pIdx[nCntIdx] = nCntVtx + m_Mesh.nNumVtx_U;
			pIdx[nCntIdx + 1] = nCntVtx;
			nCntVtx++;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//==========================================
//  �e�f�[�^�̌v�Z����
//==========================================
void CObject_Mesh::CalcData(void)
{
	m_Mesh.nNumVtx_U = m_Mesh.nNumMesh_U + 1;
	m_Mesh.nNumVtx_V = m_Mesh.nNumMesh_V + 1;
	m_Mesh.nNumVtx = m_Mesh.nNumVtx_U * m_Mesh.nNumVtx_V;
	m_Mesh.nNumIdx = (m_Mesh.nNumVtx * 2) - (2 * (abs(m_Mesh.nNumMesh_U - m_Mesh.nNumMesh_V)) + 4);
	m_Mesh.nNumMesh = m_Mesh.nNumIdx - 2;
}

//==========================================
//  ���b�V���t�B�[���h��̑��ݔ���(����̂�)
//==========================================
bool CObject_Mesh::OnMesh(const D3DXVECTOR3 pos)
{
	//���[�J���ϐ��錾
	int nCntPoint = 0;

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//��̑��ݔ���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = nCnt; //��
		int IdxEnd = nCnt + 1; //�E
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���̑��ݔ���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = (m_Mesh.nNumVtx_U * m_Mesh.nNumMesh_V) + nCnt + 1; //�E
		int IdxEnd = IdxStart - 1; //��
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//�E�̔���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxStart = (nCnt + 1) * m_Mesh.nNumVtx_U - 1; //��
		int IdxEnd = IdxStart + m_Mesh.nNumVtx_U; //��
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���̔���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxEnd = nCnt * m_Mesh.nNumVtx_V; //��
		int IdxStart = IdxEnd + m_Mesh.nNumVtx_U; //��
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return true;
}

//==========================================
//  ���b�V���t�B�[���h��̑��ݔ���(�����߂�)
//==========================================
bool CObject_Mesh::OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 *pVecLine, D3DXVECTOR3 *pVecToPos)
{
	//���[�J���ϐ��錾
	int nCntPoint = 0;

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//��̑��ݔ���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = nCnt; //��
		int IdxEnd = nCnt + 1; //�E
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���̑��ݔ���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = (m_Mesh.nNumVtx_U * m_Mesh.nNumMesh_V) + nCnt + 1; //�E
		int IdxEnd = IdxStart - 1; //��
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//�E�̔���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxStart = (nCnt + 1) * m_Mesh.nNumVtx_U - 1; //��
		int IdxEnd = IdxStart + m_Mesh.nNumVtx_U; //��
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���̔���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxEnd = nCnt * m_Mesh.nNumVtx_V; //��
		int IdxStart = IdxEnd + m_Mesh.nNumVtx_U; //��
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//�͈͊O�������ꍇfalse
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
	
	return true;
}

bool CObject_Mesh::CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const
{
	return (posEnd.z - posStart.z) * (posJudge.x - posStart.x) - (posEnd.x - posStart.x) * (posJudge.z - posStart.z) < 0.0f;
}
