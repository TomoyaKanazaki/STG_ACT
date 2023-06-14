//==========================================
//
//  x�I�u�W�F�N�g�N���X(object_x.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_x.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CObject_X::CObject_X(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_mtxWorld = {};
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject_X::~CObject_X()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject_X::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//���̕ۑ�
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		"data\\MODEL\\Player\\player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh
	);

	//�}�e���A�������̃|�C���^���m�ۂ���
	if (m_pTexture == NULL)
	{
		m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];
	}
	else
	{
		return E_FAIL;
	}

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`����ۑ����A�Ǘ��ԍ����擾����
			int nNumTexID = CManager::GetTexture()->Regist(pMat[nCntMat].pTextureFilename);

			//�e�N�X�`�������蓖�Ă�
			m_pTexture[nCntMat] = CManager::GetTexture()->GetAddress(nNumTexID);

			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]
			);
		}
		else
		{
			m_pTexture[nCntMat] = NULL;
		}
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject_X::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
		{
			if (m_pTexture[nCnt] != NULL)
			{
				m_pTexture[nCnt]->Release();
				m_pTexture[nCnt] = NULL;
			}
		}
		delete[] m_pTexture;
		m_pTexture = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CObject_X::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CObject_X::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���ւ̃|�C���^

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

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f���̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă���}�e���A���𕜌�
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  ��������
//==========================================
CObject_X * CObject_X::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CObject_X *pObject_X = NULL;

	//NULL�`�F�b�N
	if (pObject_X == NULL)
	{
		//���������m��
		pObject_X = new CObject_X;
	}

	//������
	if (pObject_X != NULL)
	{
		pObject_X->Init(pos, size, rot);
	}

	//�|�C���^��Ԃ�
	return pObject_X;
}
