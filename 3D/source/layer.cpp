//==========================================
//
//  �K�w�\���Ǘ��N���X(layer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "layer.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CLayer::LAYERDATA *CLayer::m_pData = NULL;
int CLayer::m_nNumLayer = 0;

//==========================================
//  �}�N����`
//==========================================
#define TXTLAYER "data\\TXT\\LayerData.txt" //�K�w�\���̏��

//==========================================
//  �R���X�g���N�^
//==========================================
CLayer::CLayer()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLayer::~CLayer()
{

}

//==========================================
//  ����������
//==========================================
void CLayer::Init(void)
{

}

//==========================================
//  �I������
//==========================================
void CLayer::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CLayer::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CLayer::Draw(void)
{

}

//==========================================
//  �ݒ菈��
//==========================================
CLayer::LAYERDATA *CLayer::Set(LAYERS type)
{
	//�K�w�\���̏���n��
	return &m_pData[type];
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CLayer::Load(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����
	char aStr[256]; //�s�v�ȕ�����̋L�^�p

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(TXTLAYER, "r");

	if (pFile != NULL)
	{
		//�s�v�ȕ�����̎擾
		while (1)
		{
			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "NUM_LAYER") == 0)
			{
				break;
			}
		}

		//�K�w�\�����̐����擾
		fscanf(pFile, "%s", &aStr[0]); // =
		fscanf(pFile, "%d", &m_nNumLayer);

		//���C���[��񂪑��݂���ꍇ
		if (m_nNumLayer != 0)
		{
			//���������m�ۂ���
			m_pData = new LAYERDATA[m_nNumLayer];
		}

		//NULL�`�F�b�N
		if (m_pData != NULL)
		{
			for (int nCntLayer = 0; nCntLayer < m_nNumLayer; nCntLayer++)
			{
				//�s�v�ȕ�����̎擾
				while (1)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strcmp(&aStr[0], "NUM_MODEL") == 0)
					{
						break;
					}
				}

				//���f�������擾
				fscanf(pFile, "%d", &m_pData[nCntLayer].nNumModel);

				//���f�������݂���ꍇ
				if (m_pData[nCntLayer].nNumModel != 0)
				{
					//���������m�ۂ���
					m_pData[nCntLayer].pModelID = new int[m_pData[nCntLayer].nNumModel];
					m_pData[nCntLayer].pParentID = new int[m_pData[nCntLayer].nNumModel];
					m_pData[nCntLayer].pPos = new D3DXVECTOR3[m_pData[nCntLayer].nNumModel];
					m_pData[nCntLayer].pRot = new D3DXVECTOR3[m_pData[nCntLayer].nNumModel];
				}

				//NULL�`�F�b�N
				if (m_pData[nCntLayer].pModelID != NULL && m_pData[nCntLayer].pParentID != NULL)
				{
					for (int nCntModel = 0; nCntModel < m_pData[nCntLayer].nNumModel; nCntModel++)
					{
						//���g���g�p���郂�f���̎擾
						fscanf(pFile, "%s", &aStr[0]); // MODELID
						fscanf(pFile, "%d", &m_pData[nCntLayer].pModelID[nCntModel]);

						//�e���f���̃C���f�b�N�X���擾
						fscanf(pFile, "%s", &aStr[0]); // ParentID
						fscanf(pFile, "%d", &m_pData[nCntLayer].pParentID[nCntModel]);

						//�e���f���̃C���f�b�N�X���擾
						fscanf(pFile, "%s", &aStr[0]); // POS
						fscanf(pFile, "%f", &m_pData[nCntLayer].pPos[nCntModel].x);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pPos[nCntModel].y);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pPos[nCntModel].z);

						//�e���f���̃C���f�b�N�X���擾
						fscanf(pFile, "%s", &aStr[0]); // ROT
						fscanf(pFile, "%f", &m_pData[nCntLayer].pRot[nCntModel].x);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pRot[nCntModel].y);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pRot[nCntModel].z);
					}
				}
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//==========================================
//  �j��
//==========================================
void CLayer::UnLoad(void)
{
	//���������J������
	if (m_pData != NULL)
	{
		delete m_pData->pModelID;
		m_pData->pModelID = NULL;

		delete m_pData->pParentID;
		m_pData->pParentID = NULL;

		delete m_pData->pPos;
		m_pData->pPos = NULL;

		delete m_pData->pRot;
		m_pData->pRot = NULL;

		delete m_pData;
		m_pData = NULL;
	}
}
