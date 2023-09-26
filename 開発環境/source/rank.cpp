//==========================================
//
//  ����(rank.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "rank.h"
#include "number.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CRank::CRank(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < RANK_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
		m_aRank[nCnt] = 0;
	}
	m_nRank = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CRank::~CRank()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CRank::Init(void)
{
	//�\�����鐔���̌v�Z
	CalcRank();

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < RANK_DIGIT; nCnt++)
	{
		//NULL�`�F�b�N
		if (m_apNumber[nCnt] == NULL)
		{
			//����������W���v�Z
			D3DXVECTOR3 NumPos = CalcPos(nCnt);

			if (nullptr == (m_apNumber[nCnt] = CNumber::Create(NumPos, D3DXVECTOR3(m_size.x / RANK_DIGIT, m_size.y, m_size.z), m_rot, m_aRank[nCnt])))
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
void CRank::Uninit(void)
{
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CRank::Update(void)
{

}

//==========================================
//  �`�揈��
//==========================================
void CRank::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CRank *CRank::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nRank)
{
	//�C���X�^���X����
	CRank *pRank = NULL;

	//NULL�`�F�b�N
	if (pRank == NULL)
	{
		//���������m��
		pRank = new CRank;
	}

	pRank->m_pos = pos;
	pRank->m_size = size;
	pRank->m_nRank = nRank;

	//������
	if (pRank != NULL)
	{
		pRank->Init();
	}

	//�|�C���^��Ԃ�
	return pRank;
}

//==========================================
//  �v�Z����
//==========================================
void CRank::CalcRank(void)
{
	//���[�J���ϐ��錾
	int nCalc = m_nRank; //�ꎞ�ۊ�

	//�e�N�X�`�����W�̌v��
	for (int nCntRank = RANK_DIGIT - 1; nCntRank >= 0; nCntRank--)
	{
		m_aRank[nCntRank] = nCalc % 10;
		nCalc /= 10;
	}
}

//==========================================
//  �����̍��W���v�Z���鏈��
//==========================================
D3DXVECTOR3 CRank::CalcPos(int nCnt)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 NumPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//x���W���v�Z����
	NumPos.x = m_pos.x + ((m_size.x / (RANK_DIGIT * 2)) * (nCnt * 2 + 1));

	//y���W��������
	NumPos.y = m_pos.y;

	//�l��Ԃ�
	return NumPos;
}
