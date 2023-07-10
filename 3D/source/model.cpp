//==========================================
//
//  ���f���N���X(model.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �}�N����`
//==========================================
#define TXTFILENAME_MODEL "data\\TXT\\ModelData.txt" //���f�������������e�L�X�g�t�@�C���̃p�X
#define SHARE_PASS_MODEL "data\\MODEL\\" //�S�Ă�X�t�@�C���ɋ��ʂ��鑊�΃p�X

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CModel::MODEL CModel::m_Model[64] = {};
int CModel::m_nNumAll = 0;
char CModel::m_sFilePass[MAX_MODEL][128] = {};
bool CModel::m_bLoad = false;
int CModel::m_nNum = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CModel::CModel(int nPriority) : CObject(nPriority)
{
	m_Info.pTexture = NULL;
	m_Info.pMesh = NULL;
	m_Info.pBuffMat = NULL;
	m_Info.dwNumMat = 0;
	m_Info.mtxWorld = {};
	m_pParent = NULL;
	m_nSelfID = 0;
	m_nNum++;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CModel::~CModel()
{
	m_nNum--;
}

//==========================================
//  ����������
//==========================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CModel::Uninit(void)
{
	//�������g�̔j��
	this->Release();
}

//==========================================
//  �X�V����
//==========================================
void CModel::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CModel::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent; //�e�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat; //�}�e���A���ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�e�}�g���b�N�X�̐ݒ�
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->m_Info.mtxWorld;

		//���[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
		D3DXMatrixMultiply
		(
			&m_Info.mtxWorld,
			&m_Info.mtxWorld,
			&mtxParent
		);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_Info.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_Info.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_Info.pTexture[nCntMat]);

		//���f���̕`��
		m_Info.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă���}�e���A���𕜌�
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  ��������
//==========================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nModelID, CModel *m_pParent)
{
	//�C���X�^���X����
	CModel *pModel = NULL;

	//NULL�`�F�b�N
	if (pModel == NULL)
	{
		//���������m��
		pModel = new CModel;
	}

	//�e����̕ۑ�
	pModel->m_pParent = m_pParent;
	pModel->m_nSelfID = nModelID;

	//�e����̐ݒ�
	if (m_nNumAll > pModel->m_nSelfID)
	{
		pModel->m_Info = m_Model[pModel->m_nSelfID];
		pModel->m_pos = pos;
		pModel->m_rot = rot;
	}

	//������
	if (pModel != NULL)
	{
		pModel->Init();
	}

	//�|�C���^��Ԃ�
	return pModel;
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
HRESULT CModel::Load(void)
{
	if (m_bLoad)
	{
		return E_FAIL;
	}

	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����
	int nNumModel; //�ǂݍ��ރe�N�X�`����
	char aStr[256]; //�s�v�ȕ�����̋L�^�p

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(TXTFILENAME_MODEL, "r");

	if (pFile != NULL)
	{
		//�s�v�ȕ�����̓ǂݍ���
		for (int nCntDiscard = 0; nCntDiscard < 13; nCntDiscard++)
		{
			fscanf(pFile, "%s", &aStr[0]);
		}

		//�e�N�X�`�����̓ǂݍ���
		fscanf(pFile, "%d", &nNumModel);

		//�����i�[����
		for (int nCnt = 0; nCnt < nNumModel; nCnt++)
		{
			m_Model[nCnt].pTexture = NULL;
			m_Model[nCnt].pMesh = NULL;
			m_Model[nCnt].pBuffMat = NULL;
			m_Model[nCnt].dwNumMat = 0;
			m_Model[nCnt].mtxWorld = {};
		}

		//1��ވȏ�̃��f��������ꍇ
		if (nNumModel > 0)
		{
			//�e�N�X�`�������̋L�^
			m_nNumAll = nNumModel;

			//�s�v�ȕ�����̓ǂݍ���
			for (int nCntDiscard = 0; nCntDiscard < 4; nCntDiscard++)
			{
				fscanf(pFile, "%s", &aStr[0]);
			}

			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			//���f���̓ǂݍ���
			for (int nCnt = 0; nCnt < nNumModel; nCnt++)
			{
				//x�t�@�C���̃p�X
				char sTexName[256];

				//���ʂ̃p�X���擾
				strcpy(&sTexName[0], SHARE_PASS_MODEL);

				//�t�@�C�����̓ǂݍ���
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					fscanf(pFile, "%s", &aStr[0]);
				}

				//�p�X�ƃt�@�C�����̘A��
				strcat(&sTexName[0], &aStr[0]);

				//X�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX
				(
					&sTexName[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_Model[nCnt].pBuffMat,
					NULL,
					&m_Model[nCnt].dwNumMat,
					&m_Model[nCnt].pMesh
				);

				//�}�e���A�������̃|�C���^���m�ۂ���
				if (m_Model[nCnt].pTexture == NULL)
				{
					m_Model[nCnt].pTexture = new LPDIRECT3DTEXTURE9[m_Model[nCnt].dwNumMat];
				}
				else
				{
					return E_FAIL;
				}

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_Model[nCnt].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)m_Model[nCnt].dwNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ۑ����A�Ǘ��ԍ����擾����
						int nNumTexID = CManager::GetTexture()->Regist(pMat[nCntMat].pTextureFilename);

						//�e�N�X�`�������蓖�Ă�
						m_Model[nCnt].pTexture[nCntMat] = CManager::GetTexture()->GetAddress(nNumTexID);

						D3DXCreateTextureFromFile
						(
							pDevice,
							pMat[nCntMat].pTextureFilename,
							&m_Model[nCnt].pTexture[nCntMat]
						);
					}
					else
					{
						m_Model[nCnt].pTexture[nCntMat] = NULL;
					}
				}

				//�ǂݍ��񂾃e�N�X�`���̃p�X���L�^
				strcpy(&m_sFilePass[nCnt][0], &sTexName[0]);

				//�s�v�ȕ�����̓ǂݍ���
				fscanf(pFile, "%s", &aStr[0]);
			}

			//�ǂݍ��݊����t���O�𗧂Ă�
			m_bLoad = true;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �j������
//==========================================
void CModel::UnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		//���b�V���̔j��
		if (m_Model[nCnt].pMesh != NULL)
		{
			m_Model[nCnt].pMesh->Release();
			m_Model[nCnt].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (m_Model[nCnt].pBuffMat != NULL)
		{
			m_Model[nCnt].pBuffMat->Release();
			m_Model[nCnt].pBuffMat = NULL;
		}

		//�e�N�X�`���̔j��
		if (m_Model[nCnt].pTexture != NULL)
		{
			for (int nCntMat = 0; nCntMat < (int)m_Model[nCnt].dwNumMat; nCntMat++)
			{
				if (m_Model[nCnt].pTexture[nCntMat] != NULL)
				{
					m_Model[nCnt].pTexture[nCntMat]->Release();
					m_Model[nCnt].pTexture[nCntMat] = NULL;
				}
			}
			delete[] m_Model[nCnt].pTexture;
			m_Model[nCnt].pTexture = NULL;
		}
	}
}
