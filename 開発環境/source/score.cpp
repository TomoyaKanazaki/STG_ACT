//==========================================
//
//  �X�R�A�N���X(score.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "score.h"
#include "number.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �ÓI�����o�ϐ�
//==========================================
int CScore::m_prevScore = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aScore[nCnt] = 0;
	}
	m_nScore = 0;
	m_fScale = 1.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CScore::~CScore()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CScore::Init(void)
{
	//�v�Z����
	CalcScore();

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		//NULL�`�F�b�N
		if (m_apNumber[nCnt] == NULL)
		{
			//����������W���v�Z
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (nullptr == (m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(m_size.x / SCORE_DIGIT, m_size.y, m_size.z), m_rot, m_aScore[nCnt])))
			{
				return E_FAIL;
			}
		}
	}

	//�^�C�v�����蓖�Ă�
	SetType(TYPE_SCORE);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CScore::Uninit(void)
{
	m_prevScore = m_nScore;
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CScore::Update(void)
{
	CManager::GetDebugProc()->Print("�X�R�A�{�� : %f\n", m_fScale);
}

//==========================================
//  �`�揈��
//==========================================
void CScore::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nScoreDeff)
{
	//�C���X�^���X����
	CScore *pScore = NULL;

	//NULL�`�F�b�N
	if (pScore == NULL)
	{
		//���������m��
		pScore = new CScore;
	}

	//�l�����蓖�Ă�
	pScore->m_nScore = nScoreDeff;
	pScore->m_pos = pos;
	pScore->m_size = size;
	pScore->m_rot = rot;

	//������
	if (pScore != NULL)
	{
		pScore->Init();
	}

	//�|�C���^��Ԃ�
	return pScore;
}

//==========================================
//  �v�Z����
//==========================================
void CScore::CalcScore(void)
{
	//���[�J���ϐ��錾
	int nCalc = m_nScore; //�ꎞ�ۊ�

	//�e�N�X�`�����W�̌v��
	for (int nCntScore = SCORE_DIGIT - 1; nCntScore >= 0; nCntScore--)
	{
		m_aScore[nCntScore] = nCalc % 10;
		nCalc /= 10;
	}
}

//==========================================
//  ���Z����
//==========================================
void CScore::Add(const int nAdd)
{
	//�X�R�A�����Z����
	m_nScore += (int)((float)nAdd * m_fScale);

	//�v�Z����
	CalcScore();

	//�v�Z���ʂ����蓖�Ă�
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_aScore[nCnt]);
	}
}

//==========================================
//  �����̍��W���v�Z���鏈��
//==========================================
D3DXVECTOR3 CScore::CalcPos(int nCnt)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x���W���v�Z����
	NumPos.x = m_pos.x + ((m_size.x / (SCORE_DIGIT * 2)) * (nCnt * 2 + 1));

	//y���W��������
	NumPos.y = m_pos.y;

	//�l��Ԃ�
	return NumPos;
}
