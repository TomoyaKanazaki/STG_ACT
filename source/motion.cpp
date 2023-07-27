//==========================================
//
//  ���[�V�����N���X(moton.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "motion.h"
#include "model.h"

//==========================================
//  �}�N����`
//==========================================
#define TXTFILENAME_MOTION "data\\TXT\\MotionData.txt" //���[�V���������������e�L�X�g�t�@�C���̃p�X

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CMotion::INFO *CMotion::m_pInfo = NULL;
int CMotion::m_nNumMotion = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CMotion::CMotion()
{
	m_ppModel = NULL;
	m_nMotion = MOTION_NONE;
	m_Info = {};
	m_nNumModel = 0;
	m_nCntFrame = 0;
	m_nCntKey = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CMotion::~CMotion()
{

}

//==========================================
//  �X�V����
//==========================================
void CMotion::Update(void)
{
	//NULL�`�F�b�N
	if (m_ppModel != NULL)
	{
		//�L�[�̗L�����m�F
		if (m_Info.nNumKey > 0)
		{
			int nNowMotion = m_nMotion; //���݂̃��[�V�����ԍ�
			int nNowKey = m_nCntKey; // ���݂̃L�[
			int nNextkey = (nNowKey + 1) % m_Info.nNumKey; //���̃L�[
			int nFrame = m_Info.pKeyInfo[nNowKey].nFrame;

			//����(����)
			float fFrame = ((float)m_nCntFrame / (float)nFrame);

			//���f�������̃��[�V������ݒ�
			for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
			{
				//�O��̒l���擾
				m_oldKey.pos = m_ppModel[nCntModel]->GetPos();
				m_oldKey.rot = m_ppModel[nCntModel]->GetRot();

				//�������Z�o
				D3DXVECTOR3 posDeff = D3DXVECTOR3
				(
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].pos.x - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.x,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].pos.y - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.y,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].pos.z - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.z
				);
				D3DXVECTOR3 rotDeff = D3DXVECTOR3
				(
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].rot.x - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.x,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].rot.y - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.y,
					m_Info.pKeyInfo[nNextkey].pKey[nCntModel].rot.z - m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.z
				);

				//�p�x�̕␳
				if (rotDeff.x < -D3DX_PI) //x
				{
					rotDeff.x += D3DX_PI * 2;
				}
				else if (rotDeff.x > D3DX_PI)
				{
					rotDeff.x += -D3DX_PI * 2;
				}

				if (rotDeff.y < -D3DX_PI) //y
				{
					rotDeff.y += D3DX_PI * 2;
				}
				else if (rotDeff.y > D3DX_PI)
				{
					rotDeff.y += -D3DX_PI * 2;
				}

				if (rotDeff.z < -D3DX_PI) //z
				{
					rotDeff.z += D3DX_PI * 2;
				}
				else if (rotDeff.z > D3DX_PI)
				{
					rotDeff.z += -D3DX_PI * 2;
				}

				//���݂̒l���Z�o
				D3DXVECTOR3 posDest = D3DXVECTOR3
				(
					m_oldKey.pos.x + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.x + posDeff.x * fFrame,
					m_oldKey.pos.y + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.y + posDeff.y * fFrame,
					m_oldKey.pos.z + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].pos.z + posDeff.z * fFrame
				);
				D3DXVECTOR3 rotDest = D3DXVECTOR3
				(
					m_oldKey.rot.x + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.x + rotDeff.x * fFrame,
					m_oldKey.rot.y + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.y + rotDeff.y * fFrame,
					m_oldKey.rot.z + m_Info.pKeyInfo[nNowKey].pKey[nCntModel].rot.z + rotDeff.z * fFrame
				);

				//�Z�o�����l�̓K�p
				m_ppModel[nCntModel]->SetPos(posDest);
				m_ppModel[nCntModel]->SetRot(rotDest);
			}

			//�t���[���J�E���g�����Z
			m_nCntFrame++;

			//�L�[�̍X�V���`�F�b�N
			if (m_Info.pKeyInfo[nNowKey].nFrame != 0)
			{
				if (m_nCntFrame == nFrame)
				{
					//�L�[�̍X�V
					m_nCntKey = nNextkey;
					m_nCntFrame = 0;
				}
			}
			else
			{
				m_nCntKey = 0;
				m_nCntFrame = 0;
			}
		}
	}
}

//==========================================
//  ���f���̐ݒ菈��
//==========================================
void CMotion::SetModel(CModel **ppModel, int nNum, CHARA type)
{
	//���f�����L�^
	m_ppModel = ppModel;

	//���f�������L�^
	m_nNumModel = nNum;

	//�L�����N�^�[�����L�^
	m_nMotion = type;

	//�g�p���郂�[�V������ݒ�
	m_Info = m_pInfo[type];
}

//==========================================
//  ���[�V�����̐ݒ菈��
//==========================================
void CMotion::Set(CHARA type)
{
	//�L�����N�^�[����ݒ�
	m_nMotion = type;

	//�g�p���郂�[�V������ݒ�
	m_Info = m_pInfo[type];

	//�J�E���^�[�����Z�b�g
	m_nCntKey = 0;
	m_nCntFrame = 0;
}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CMotion::Load(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����
	char aStr[256]; //�s�v�ȕ�����̋L�^�p
	int nCntInfo = 0; //���݂̃��[�V�����ԍ�
	int nCntKey = 0; //���݂̃L�[�ԍ�
	int nCntModel = 0; //���݂̃��f���ԍ�

	//�t�@�C����ǂݎ���p�ŊJ��
	pFile = fopen(TXTFILENAME_MOTION, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			//��������擾
			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "NUM_MOTION") == 0)
			{
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_nNumMotion); //���[�V�������擾

				//���[�V�������̃��������m��
				m_pInfo = new INFO[m_nNumMotion];
			}
			else if (strcmp(&aStr[0], "LOOP") == 0)
			{
				//���[�v�̗L�����擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].bLoop);
			}
			else if (strcmp(&aStr[0], "NUM_KEY") == 0)
			{
				//�L�[���̎擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].nNumKey);

				//�L�[�����̃��������m��
				m_pInfo[nCntInfo].pKeyInfo = new KEY_INFO[m_pInfo[nCntInfo].nNumKey];
			}
			else if (strcmp(&aStr[0], "NUM_MODEL") == 0)
			{
				//���f�����̎擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].nNumModel);

				//���f�������̃��������m��
				for (int nCnt = 0; nCnt < m_pInfo[nCntInfo].nNumKey; nCnt++)
				{
					m_pInfo[nCntInfo].pKeyInfo[nCnt].pKey = new KEY[m_pInfo[nCntInfo].nNumModel];
				}
			}
			else if (strcmp(&aStr[0], "FRAME") == 0)
			{
				//�t���[�������擾
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_pInfo[nCntInfo].pKeyInfo[nCntKey].nFrame);
			}
			else if (strcmp(&aStr[0], "POS") == 0)
			{
				//���W���擾
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 pos;
				fscanf(pFile, "%f", &pos.x);
				fscanf(pFile, "%f", &pos.y);
				fscanf(pFile, "%f", &pos.z);

				m_pInfo[nCntInfo].pKeyInfo[nCntKey].pKey[nCntModel].pos = pos;
			}
			else if (strcmp(&aStr[0], "ROT") == 0)
			{
				//�p�x���擾
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 rot;
				fscanf(pFile, "%f", &rot.x);
				fscanf(pFile, "%f", &rot.y);
				fscanf(pFile, "%f", &rot.z);

				m_pInfo[nCntInfo].pKeyInfo[nCntKey].pKey[nCntModel].rot = rot;
			}
			else if (strcmp(&aStr[0], "END_MOTIONSET") == 0)
			{
				//���[�V�����ԍ���i�߂�
				nCntInfo++;

				//�L�[�ԍ��ƃ��f���ԍ������Z�b�g����
				nCntModel = 0;
				nCntKey = 0;
			}
			else if (strcmp(&aStr[0], "END_KEYSET") == 0)
			{
				//�L�[�ԍ���i�߂�
				nCntKey++;

				//���f���ԍ������Z�b�g����
				nCntModel = 0;
			}
			else if (strcmp(&aStr[0], "END_KEY") == 0)
			{
				//���f���ԍ���i�߂�
				nCntModel++;
			}
			if (strcmp(&aStr[0], "END_SCRIPT") == 0)
			{
				//�I�[
				break;
			}
		}
		fclose(pFile);
	}
}

//==========================================
//  ���̔j��
//==========================================
void CMotion::UnLoad(void)
{
	//���[�V�������̔j��
	for (int nCntMotion = 0; nCntMotion < m_nNumMotion; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < m_pInfo[nCntMotion].nNumKey; nCntKey++)
		{
			delete[] m_pInfo[nCntMotion].pKeyInfo[nCntKey].pKey;
			m_pInfo[nCntMotion].pKeyInfo[nCntKey].pKey = NULL;
		}
		delete[] m_pInfo[nCntMotion].pKeyInfo;
		m_pInfo[nCntMotion].pKeyInfo = NULL;
	}
	delete[] m_pInfo;
	m_pInfo = NULL;
}
