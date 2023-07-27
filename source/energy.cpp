//==========================================
//
//  �G�l���M�[�N���X(energy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "energy.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "gamemanager.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CEnergy::m_fMax = 650.0f;
const float CEnergy::m_fAdd = CEnergy::m_fMax * 0.05f;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnergy::CEnergy()
{
	m_fEnergy = 0.0f;
	m_fBaseHight = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnergy::~CEnergy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnergy::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_ENERGY);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnergy::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnergy::Update(void)
{
	//�ő�l�̕␳
	if (m_fEnergy > m_fMax)
	{
		m_fEnergy = m_fMax;
	}

	//�Q�[�W�̐L�k
	float fSizeMove = m_size.y, fSizeDest = m_fEnergy, fSizeDiff; //�v�Z�p�ϐ�
	fSizeDiff = fSizeDest - fSizeMove; //���݂̑傫���ƖڕW�̑傫���̍��������߂�
	m_size.y += fSizeDiff * 0.1f; //�l��␳���ĉ��Z����

	//�X�V���̓K�p
	CObject2D::Update();

	//�G�l���M�[�����炷
	if (CGameManager::GetState() == CGameManager::BLADE)
	{
		m_fEnergy--;
	}

#if _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		m_fEnergy = m_fMax;
	}
#endif
}

//==========================================
//  �`�揈��
//==========================================
void CEnergy::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CEnergy *CEnergy::Create(const D3DXVECTOR3 pos, const float fWidth)
{
	//�C���X�^���X����
	CEnergy *pEnergy = NULL;

	//NULL�`�F�b�N
	if (pEnergy == NULL)
	{
		//���������m��
		pEnergy = new CEnergy;
	}

	//�l�����蓖�Ă�
	pEnergy->m_pos = pos;
	pEnergy->m_fBaseHight = pos.y;

	//�����l�𐶐�����
	pEnergy->m_size.x = fWidth;
	pEnergy->m_size.y = pEnergy->m_fEnergy;

	//������
	if (pEnergy != NULL)
	{
		pEnergy->Init();
	}

	//�|�C���^��Ԃ�
	return pEnergy;
}

