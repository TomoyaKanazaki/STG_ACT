//==========================================
//
//  �����L���O(ranking.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ranking.h"
#include "score.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const char CRanking::m_sPass[128] = "data\\BIN\\Ranking.bin";
int CRanking::m_nNumData = 1;
int *CRanking::m_pScore = NULL;
int CRanking::m_nRank = 0;
int CRanking::m_nScore = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CRanking::CRanking()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CRanking::~CRanking()
{

}

//==========================================
//  ����������
//==========================================
void CRanking::Init(void)
{
	//�O��܂ł̃f�[�^��ǂݍ���
	Load();
}

//==========================================
//  �I������
//==========================================
void CRanking::Uninit(void)
{
	Reset();
}

//==========================================
//  �X�V����
//==========================================
void CRanking::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CRanking::Draw(void)
{

}

//==========================================
//  �ǂݍ��ݏ���
//==========================================
void CRanking::Load(void)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����

	//�t�@�C����ǂݍ��ݐ�p�ŊJ��
	pFile = fopen(&m_sPass[0], "rb");

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		//�f�[�^�����擾
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//�f�[�^���擾
		Reset();
		m_pScore = new int[m_nNumData];
		fread(m_pScore, sizeof(int), m_nNumData, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}

//==========================================
//  �����o������
//==========================================
void CRanking::Save(int nNewScore)
{
	//���[�J���ϐ��錾
	FILE *pFile; //�t�@�C����

	//�t�@�C����ǂݍ��ݐ�p�ŊJ��
	pFile = fopen(&m_sPass[0], "rb");

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		//�f�[�^�����擾
		fread(&m_nNumData, sizeof(int), 1, pFile);

		//�f�[�^���擾
		Reset();
		m_pScore = new int[m_nNumData + 1];
		fread(m_pScore, sizeof(int), m_nNumData, pFile);

		//�t�@�C�������
		fclose(pFile);
	}

	//�f�[�^��ǉ�
	m_pScore[m_nNumData] = nNewScore;
	m_nScore = nNewScore;
	m_nNumData++;

	//�\�[�g����
	qsort
	(
		m_pScore,
		m_nNumData ,
		sizeof(int),
		Descending
	);

	//�t�@�C�����������ݐ�p�ŊJ��
	pFile = fopen(&m_sPass[0], "wb");

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		//�f�[�^�����擾
		fwrite(&m_nNumData, sizeof(int), 1, pFile);

		//�f�[�^���擾
		fwrite(m_pScore, sizeof(int), m_nNumData, pFile);

		//�t�@�C�������
		fclose(pFile);
	}

	//���ʂ�ݒ�
	for (int nCnt = 0; nCnt < m_nNumData; nCnt++)
	{
		if (m_pScore[nCnt] == nNewScore)
		{
			m_nRank = nCnt + 1;
			break;
		}
	}

	//�f�[�^��j��
	Reset();
}

//==========================================
//  �X�R�A�̏�����
//==========================================
void CRanking::Reset(void)
{
	//�X�R�A�����ɑ��݂��Ă�����폜����
	if (m_pScore != NULL)
	{
		delete[] m_pScore;
		m_pScore = NULL;
	}
}

//==========================================
//  �~���w��
//==========================================
int CRanking::Descending(const void * n0, const void * n1)
{
	//n0��n1�̒l���r�������ʂɂ���ĕԂ�l�����肷��
	if (*(int *)n0 < *(int *)n1)
	{
		return 1;
	}
	else if (*(int *)n0 > *(int *)n1)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
