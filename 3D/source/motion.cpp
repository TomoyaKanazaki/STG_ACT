//==========================================
//
//  ���[�V�����N���X(motion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "motion.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CMotion::CMotion()
{
	m_apInfo = NULL;
	m_nNumAll = 0;
	m_nType = 0;
	m_nNumKey = 0;
	m_nKey = 0;
	m_nNumModel = 0;
	m_bLoop = false;
	m_bFinish = false;
	m_pModel = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CMotion::~CMotion()
{

}

//==========================================
//  ����������
//==========================================
void CMotion::Init(char *sFileName)
{
	//���[�J���ϐ��錾
	char aStr[128]; //�p���p
	int nNumModel = 0; //���f������r�p
	D3DXVECTOR3 LoadPos, LoadRot;

	//���[�V�����t�@�C����ǂݍ���
	FILE *pFile = fopen(sFileName, "r");

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		//�L�����N�^�[�Z�b�g�܂Ŕ�΂�
		do
		{
			fscanf(pFile, "%s", &aStr[0]);
		} while (strcmp(aStr, "CHARACTERSET") != 0);

		//���f����
		fscanf(pFile, "%s = %d	%s %s\n", &aStr[0], &nNumModel, &aStr[0], &aStr[0]);

		//���f���z�u
		if(nNumModel == m_nNumModel)
		{
			for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++, m_pModel++)
			{
				fgets(&aStr[0], 128, pFile);
				fscanf(pFile, "%s = %f %f %f", &aStr[0], &LoadPos.x, &LoadPos.y, &LoadPos.z);
				fscanf(pFile, "%s = %f %f %f\n", &aStr[0], &LoadRot.x, &LoadRot.y, &LoadRot.z);
				fgets(&aStr[0], 128, pFile);
				m_pModel->SetTransform(LoadPos, LoadRot);
			}
		}
		else
		{
			return;
		}

		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
		{
			//���[�V�����Z�b�g�܂Ŕ�΂�
			do
			{
				fscanf(pFile, "%s", &aStr[0]);
			} while (strcmp(aStr, "MOTIONSET") != 0);

			//���[�V��������
			fscanf(pFile, "%s = %d	%s %s %s %s", &aStr[0], &m_apInfo[nCntMotion].nLoop, &aStr[0], &aStr[0], &aStr[0], &aStr[0]);
			fscanf(pFile, "%s = %d	%s %s\n", &aStr[0], &m_nNumKey, &aStr[0], &aStr[0]);

			//�L�[���[�V����
			for (int nCntKey = 0; nCntKey < m_nNumKey; nCntKey++)
			{
				fgets(&aStr[0], 128, pFile);
				fscanf(pFile, "%s = %d\n", &aStr[0], &m_apInfo[nCntMotion].aKeyMotion[nCntKey].nFrame);

				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
				{
					fgets(&aStr[0], 128, pFile);
					fscanf(pFile, "%s = %f %f %f", &aStr[0], &m_apInfo[nCntMotion].aKeyMotion[nCntKey].pos[nCntModel].x, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].pos[nCntModel].y, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].pos[nCntModel].z);
					fscanf(pFile, "%s = %f %f %f\n", &aStr[0], &m_apInfo[nCntMotion].aKeyMotion[nCntKey].rot[nCntModel].x, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].rot[nCntModel].y, &m_apInfo[nCntMotion].aKeyMotion[nCntKey].rot[nCntModel].z);
					fgets(&aStr[0], 128, pFile);
				}

				fgets(&aStr[0], 128, pFile);
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}
}

//==========================================
//  �I������
//==========================================
void CMotion::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CMotion::Update(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 posCurr, rotCurr;
	D3DXVECTOR3 posDiff, rotDiff;

	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++, m_pModel++)
	{
		//���݂̈ʒu�A�p�x��ۑ�����
		posCurr = m_pModel->GetPos();
		rotCurr = m_pModel->GetRot();

		//

		//���f���ɔ��f
		m_pModel->SetTransform(posCurr + posDiff, rotCurr + rotDiff);
	}
}

//==========================================
//  �ݒ菈��
//==========================================
void CMotion::SetType(int Type)
{
	//���[�V�����̎�ނ�ݒ�
	m_nType = Type;
}

//==========================================
//  ��ނ̎擾
//==========================================
int CMotion::GetType(void)
{
	return m_nType;
}

//==========================================
//  �I��������ǂ���
//==========================================
bool CMotion::IsFinish(void)
{
	return false;
}

//==========================================
//  ���[�V�����f�[�^���쐬
CMotion *CMotion::Set(CModel *pModel, int nNumAll)
{
	//�C���X�^���X����
	CMotion *pMotion = NULL;

	//NULL�`�F�b�N
	if (pMotion == NULL)
	{
		//���������m��
		pMotion = new CMotion;
	}

	if (pMotion == NULL)
	{
		return NULL;
	}

	//����ݒ�
	pMotion->m_pModel = pModel;
	pMotion->m_nNumModel = nNumAll;

	//�|�C���^��Ԃ�
	return pMotion;
}
