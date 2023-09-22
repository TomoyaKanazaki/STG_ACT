//==========================================
//
//  �^�C�}�[�N���X(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "precompile.h"
#include "timer.h"
#include "timer_add.h"
#include "timer_sab.h"
#include "number.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < TIMER_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aTime[nCnt] = 0;
	}
	m_nCurrent = 0;
	m_nMax = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTime::~CTime()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTime::Init(void)
{
	//�\������l���v�Z
	CalcScore();

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < TIMER_DIGIT; nCnt++)
	{
		//NULL�`�F�b�N
		if (m_apNumber[nCnt] == NULL)
		{
			//����������W���v�Z
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (nullptr == (m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(m_size.x / TIMER_DIGIT, m_size.y, m_size.z), m_rot, m_aTime[nCnt])))
			{
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTime::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CTime::Update(void)
{
	//���Ԃ��v�Z����
	CalcScore();

	//�v�Z���ʂ����蓖�Ă�
	for (int nCnt = 0; nCnt < TIMER_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_aTime[nCnt]);
	}
}

//==========================================
//  �`�揈��
//==========================================
void CTime::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int max, Time kind)
{
	//�C���X�^���X����
	CTime *pTime = NULL;

	//NULL�`�F�b�N
	if (pTime == NULL)
	{
		switch (kind)
		{
		case ADD:

			pTime = new CTimer_Add;
			break;

		case SAB:

			pTime = new CTimer_Sab;
			break;
		}
	}

	//�l�����蓖�Ă�
	pTime->m_pos = pos;
	pTime->m_size = size;
	pTime->m_nMax = max;

	//������
	if (pTime != NULL)
	{
		pTime->Init();
	}

	//�|�C���^��Ԃ�
	return pTime;
}

//==========================================
//  �����̍��W���v�Z���鏈��
//==========================================
D3DXVECTOR3 CTime::CalcPos(int nCnt)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x���W���v�Z����
	NumPos.x = m_pos.x + ((m_size.x / (TIMER_DIGIT * 2)) * (nCnt * 2 + 1));

	//y���W��������
	NumPos.y = m_pos.y;

	//�l��Ԃ�
	return NumPos;
}

//==========================================
//  �v�Z����
//==========================================
void CTime::CalcScore(void)
{
	//���[�J���ϐ��錾
	int nCalc = m_nCurrent; //�ꎞ�ۊ�

	//�e�N�X�`�����W�̌v��
	for (int nCntTime = TIMER_DIGIT - 1; nCntTime >= 0; nCntTime--)
	{
		m_aTime[nCntTime] = nCalc % 10;
		nCalc /= 10;
	}
}
