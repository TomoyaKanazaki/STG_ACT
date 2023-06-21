//==========================================
//
//  ���b�V���I�u�W�F�N�g�N���X(object_mesh.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_mesh.h"
#include "manager.h"
#include "renderer.h"

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
HRESULT CObject_Mesh::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�e��ϐ��̏�����
	m_pos = pos;
	m_size = size;
	m_rot = rot;

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
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

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

	//������
	pMesh->Init(pos, size, rot);

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
//  ���b�V���t�B�[���h��̑��ݔ���
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
		//����p�ϐ��錾
		float fJudge = (pVtx[nCnt + 1].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[nCnt + 1].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		if (nCnt == m_Mesh.nNumVtx_U - 1)
		{
			fJudge = (pVtx[0].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[0].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		}

		//�͈͊O�������ꍇfalse
		if (fJudge < 0.0f)
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//���̑��ݔ���
	for (int nCnt = m_Mesh.nNumVtx - 1; nCnt > m_Mesh.nNumVtx - m_Mesh.nNumVtx_U; nCnt--)
	{
		//����p�ϐ��錾
		float fJudge = (pVtx[nCnt - 1].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[nCnt - 1].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		if (nCnt == m_Mesh.nNumVtx_U - 1)
		{
			fJudge = (pVtx[0].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[0].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		}

		//�͈͊O�������ꍇfalse
		if (fJudge < 0.0f)
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//�c�̔���p�̕ϐ�
	D3DXVECTOR3 *pPoint = NULL;

	//�K�v���̃��������m�ۂ���
	if (pPoint == NULL)
	{
		pPoint = new D3DXVECTOR3[m_Mesh.nNumVtx_V];
	}

	//�E�̒��_���擾����
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V; nCnt++)
	{
		pPoint[nCnt] = pVtx[(m_Mesh.nNumVtx_U * (nCnt + 1)) - 1].pos;
	}

	//�E�̔���
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		//����p�ϐ��錾
		float fJudge = (pPoint[nCnt + 1].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[nCnt + 1].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);
		if (nCnt == m_Mesh.nNumVtx_V - 1)
		{
			fJudge = (pPoint[0].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[0].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);
		}

		//�͈͊O�������ꍇfalse
		if (fJudge < 0.0f)
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			delete[] pPoint;
			return false;
		}
	}

	//���̒��_���擾����
	for (int nCnt = m_Mesh.nNumVtx_V - 1; nCnt >= 0; nCnt--)
	{
		pPoint[nCnt] = pVtx[m_Mesh.nNumVtx_U * nCnt].pos;
	}

	//�E�̔���
	for (int nCnt = m_Mesh.nNumVtx - m_Mesh.nNumVtx_U; nCnt >= 0; nCnt++)
	{
		//����p�ϐ��錾
		float fJudge = (pPoint[nCnt - 1].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[nCnt - 1].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);
		if (nCnt == m_Mesh.nNumVtx_U - 1)
		{
			fJudge = (pPoint[0].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[0].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);
		}

		//�͈͊O�������ꍇfalse
		if (fJudge < 0.0f)
		{
			//���_�o�b�t�@���A�����b�N
			m_pVtxBuff->Unlock();
			delete[] pPoint;
			return false;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
	
	return true;
}