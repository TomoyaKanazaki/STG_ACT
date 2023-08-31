//==========================================
//
//  �e�N�X�`���Ǘ��N���X(texture.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include <string.h>

//==========================================
//  �}�N����`
//==========================================
#define TXTFILENAME_TEX "data\\TXT\\TexData.txt" //�e�N�X�`�������������e�L�X�g�t�@�C���̃p�X
#define SHARE_PASS_TEX "data\\TEXTURE\\" //�S�Ẵe�N�X�`���t�@�C���ɋ��ʂ��鑊�΃p�X

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
bool CTexture::m_bLoad = false;

//==========================================
//  �R���X�g���N�^
//==========================================
CTexture::CTexture()
{
	m_nNumAll = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTexture::~CTexture()
{
	m_bLoad = false;
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
HRESULT CTexture::Load(void)
{
	//2�x�ڂ͂Ȃ���
	if (m_bLoad)
	{
		return E_FAIL;
	}

	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����
	int nNumTex; //�ǂݍ��ރe�N�X�`����
	char aStr[256]; //�s�v�ȕ�����̋L�^�p

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(TXTFILENAME_TEX, "r");

	if (pFile != NULL)
	{
		//�s�v�ȕ�����̓ǂݍ���
		for (int nCntDiscard = 0; nCntDiscard < 13; nCntDiscard++)
		{
			fscanf(pFile, "%s", &aStr[0]);
		}

		//�e�N�X�`�����̓ǂݍ���
		fscanf(pFile, "%d", &nNumTex);

		//�ꖇ�ȏ�̃e�N�X�`��������ꍇ
		if (nNumTex > 0)
		{
			//�e�N�X�`�������̋L�^
			m_nNumAll = nNumTex;

			//�s�v�ȕ�����̓ǂݍ���
			for (int nCntDiscard = 0; nCntDiscard < 4; nCntDiscard++)
			{
				fscanf(pFile, "%s", &aStr[0]);
			}

			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			//�e�N�X�`���̓ǂݍ���
			for (int nCnt = 0; nCnt < nNumTex; nCnt++)
			{
				//�e�N�X�`���t�@�C���̃p�X
				char sTexName[256];

				//���ʂ̃p�X���擾
				strcpy(&sTexName[0], SHARE_PASS_TEX);

				//�t�@�C�����̓ǂݍ���
				for (int nCnt2 = 0; nCnt2 < 3; nCnt2++)
				{
					fscanf(pFile, "%s", &aStr[0]);
				}

				//�p�X�ƃt�@�C�����̘A��
				strcat(&sTexName[0], &aStr[0]);

				//�e�N�X�`���̓ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(pDevice, &sTexName[0], &m_apTexture[nCnt])))
				{
					return E_FAIL;
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
			fclose(pFile);
			return E_FAIL;
		}
		fclose(pFile);
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �S�e�N�X�`���̔j������
//==========================================
void CTexture::UnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//==========================================
//  �e�N�X�`���̓o�^����
//==========================================
int CTexture::Regist(const char *pFilName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̏d����h��
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		if (strcmp(&m_sFilePass[nCnt][0], pFilName) == 0) //���ɓ����e�N�X�`�����ǂݍ��܂�Ă���ꍇ
		{
			//��ɓǂݍ��܂�Ă����e�N�X�`���̔ԍ���Ԃ�
			return nCnt;
		}
	}

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, pFilName, &m_apTexture[m_nNumAll])))
	{
		return -1;
	}
	else
	{
		//�ǂݍ��񂾃e�N�X�`���̃p�X���L�^
		strcpy(&m_sFilePass[m_nNumAll][0], pFilName);

		//���������Z
		m_nNumAll++;
	}

	//�o�^���ꂽ�e�N�X�`���̔ԍ���Ԃ�
	return m_nNumAll - 1;
}
