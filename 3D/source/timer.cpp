//==========================================
//
//  �^�C���N���X(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "timer.h"
#include "number.h"
#include "manager.h"
#include "pause.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aTime[nCnt] = 0;
	}
	m_nTime = 0;
	m_nTimeDeff = 0;
	m_nBaseTime = 0;
	m_nPauseStartTime = 0;
	m_nPauseEndTime = 0;
	m_nPauseTime = 0;
	m_bOldPause = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTimer::~CTimer()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTimer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�e�����ۑ�
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//�v�Z����
	CalcTime();

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		//NULL�`�F�b�N
		if (m_apNumber[nCnt] == NULL)
		{
			//����������W���v�Z
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (FAILED(m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(size.x / TIME_DIGIT, size.y, size.z), rot, m_aTime[nCnt])))
			{
				return E_FAIL;
			}
		}
	}

	//�^�C�v�����蓖�Ă�
	SetType(TYPE_TIMER);

	//�ϐ��̏�����
	m_nBaseTime = timeGetTime();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTimer::Uninit(void)
{
	//���������J������
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}
}

//==========================================
//  �X�V����
//==========================================
void CTimer::Update(void)
{
	//�\���\�͈͂𒴂����ꍇ
	if (m_nTime < 0 || 999 < m_nTime)
	{
		return;
	}

	//���[�J���ϐ��錾
	int nCurrentTime = timeGetTime(); //���ݎ��Ԃ̎擾 (1/1000�b)
	int nBetweenTime = 0; //����Ԃƌ��ݎ��Ԃ̍� (1/1�b)

	//�|�[�Y���Ԃ̕␳
	CalcPauseTime(nCurrentTime);

	//����Ԃƌ��ݎ��Ԃ̍����擾 (1/1�b)
	nBetweenTime = (nCurrentTime - m_nBaseTime) / 1000;

	//�c�莞�Ԃ̍X�V
	if (CManager::GetPause()->GetState() == false)
	{
		m_nTime = m_nTimeDeff - nBetweenTime;
	}

	//�v�Z����
	CalcTime();

	//�v�Z���ʂ����蓖�Ă�
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->SetNum(m_aTime[nCnt]);
	}
}

//==========================================
//  �`�揈��
//==========================================
void CTimer::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CTimer * CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nTimeDeff)
{
	//�C���X�^���X����
	CTimer *pTime = NULL;

	//NULL�`�F�b�N
	if (pTime == NULL)
	{
		//���������m��
		pTime = new CTimer;
	}

	//�l�����蓖�Ă�
	pTime->m_nTime = nTimeDeff;
	pTime->m_nTimeDeff = nTimeDeff;

	//������
	if (pTime != NULL)
	{
		pTime->Init(pos, size, rot);
	}

	//�|�C���^��Ԃ�
	return pTime;
}

//==========================================
//  �v�Z����
//==========================================
void CTimer::CalcTime(void)
{
	//���[�J���ϐ��錾
	int nCalc = m_nTime; //�ꎞ�ۊ�

	//�e�N�X�`�����W�̌v��
	for (int nCntScore = TIME_DIGIT - 1; nCntScore >= 0; nCntScore--)
	{
		m_aTime[nCntScore] = nCalc % 10;
		nCalc /= 10;
	}
}

//==========================================
//  �����̍��W���v�Z���鏈��
//==========================================
D3DXVECTOR3 CTimer::CalcPos(int nCnt)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x���W���v�Z����
	NumPos.x = m_pos.x + ((m_size.x / (TIME_DIGIT * 2)) * (nCnt * 2 + 1));

	//y���W��������
	NumPos.y = m_pos.y;

	//�l��Ԃ�
	return NumPos;
}

//==========================================
//  �|�[�Y���̏���
//==========================================
void CTimer::CalcPauseTime(int nCurrentTime)
{
	//�|�[�Y���J���ꂽ�u�Ԃ̎��Ԃ�ۑ�
	if (m_bOldPause == false && CManager::GetPause()->GetState())
	{
		m_nPauseStartTime = nCurrentTime;
	}

	//�|�[�Y��������̏���
	if (m_bOldPause && CManager::GetPause()->GetState() == false)
	{
		//�|�[�Y������ꂽ�u�Ԃ̎��Ԃ�ۑ�
		m_nPauseEndTime = nCurrentTime;

		//�|�[�Y���J����Ă������Ԃ��Z�o
		int nPauseTime = m_nPauseEndTime - m_nPauseStartTime;

		//�|�[�Y���J����Ă������ԕ�����Ԃ����Z����
		m_nBaseTime += nPauseTime;
	}

	m_bOldPause = CManager::GetPause()->GetState();
}
