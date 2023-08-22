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
#include "object_mesh.h"
#include "collision.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  �}�N����`
//==========================================
#define WIND_AREA (100.0f) //���������͈�

//==========================================
//  �R���X�g���N�^
//==========================================
COrbit::COrbit()
{
	m_parent = NULL;
	m_nLife = 0;
	m_nNumVtx = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_offset[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_offset[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_offset[nCnt].mtxWorld = {};
	}
	m_pMesh = NULL;
	m_pVtxPos = NULL;
	m_fLength = 0.0f;
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
	m_nNumVtx = (m_nLife + 1) * 2;

	//���b�V���𐶐�
	m_pMesh = CObject_Mesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, (float)m_nLife));

	//�F��K�p
	m_pMesh->SetColor(m_colDef);

	//���_�����̃��������m��
	m_pVtxPos = new D3DXVECTOR3[m_nNumVtx];

	//�I�t�Z�b�g�v�Z����
	CalcOffset();

	//�v���C���[���S�ƒ[�̋������Z�o
	D3DXVECTOR3 vecLength = CGameManager::GetPlayer()->GetPos() - m_pVtxPos[1];
	m_fLength = vecLength.x * vecLength.x + vecLength.z * vecLength.z;

	//���_����������
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt += 2)
	{
		m_pVtxPos[nCnt] = m_pVtxPos[0];
		m_pVtxPos[nCnt + 1] = m_pVtxPos[1];
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void COrbit::Uninit(void)
{
	//���_����j��
	delete[] m_pVtxPos;
	m_pVtxPos = NULL;

	//���b�V����j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Uninit();
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void COrbit::Update(void)
{
	//���݂̒��_���W��ۑ�
	D3DXVECTOR3 *pOldPos = new D3DXVECTOR3[m_nNumVtx];
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		pOldPos[nCnt] = m_pVtxPos[nCnt];
	}

	//���_���W�����炵�ĕۑ�����
	for (int nCnt = 2; nCnt < m_nNumVtx; nCnt++)
	{
		m_pVtxPos[nCnt] = pOldPos[nCnt - 2];
	}

	//�O��̒��_���W��j��
	delete[] pOldPos;
	pOldPos = NULL;

	//�I�t�Z�b�g�v�Z����
	CalcOffset();

	//���_���W�̓K�p
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		m_pMesh->SetVtxPos(m_pVtxPos[nCnt], nCnt);
	}

	//��[�|���S���𐶐����钸�_�̏��
	D3DXVECTOR3 aVtx[4];

	//��]�����v�Z�p�ϐ�
	D3DXVECTOR3 Direction;
	D3DXVECTOR3 vtxNew = m_pVtxPos[1] - m_pVtxPos[0];
	D3DXVECTOR3 vtxOld = m_pVtxPos[3] - m_pVtxPos[2];

	//�v�Z�p�x�N�g���̊O�ς����߂�
	D3DXVec3Cross(&Direction, &vtxNew, &vtxOld);

	if (Direction.y > 0.0f)
	{
		aVtx[0] = m_pVtxPos[0];
		aVtx[1] = m_pVtxPos[1];
		aVtx[2] = m_pVtxPos[3];
		aVtx[3] = m_pVtxPos[2];
	}
	else if (Direction.y < 0.0f)
	{
		aVtx[0] = m_pVtxPos[2];
		aVtx[1] = m_pVtxPos[3];
		aVtx[2] = m_pVtxPos[1];
		aVtx[3] = m_pVtxPos[0];
	}

	//��[�|���S���̓����蔻��
	Collision::InSquare(&aVtx[0], m_fLength);
}

//==========================================
//  �`�揈��
//==========================================
void COrbit::Draw(void)
{

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

//==========================================
//  �I�t�Z�b�g�̌v�Z����
//==========================================
void COrbit::CalcOffset(void)
{
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

		//���_���W�𒊏o
		m_pVtxPos[nCnt] = D3DXVECTOR3(m_offset[nCnt].mtxWorld._41, m_offset[nCnt].mtxWorld._42, m_offset[nCnt].mtxWorld._43);
	}
}
