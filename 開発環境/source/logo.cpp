//==========================================
//
//  ���S�N���X(logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo::CLogo(int nPriority) : CObject2D(nPriority)
{
	m_fCounter = 0.0f;
	m_type = MAX;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo::~CLogo()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo::Init(void)
{
	HRESULT h = CObject2D::Init();
	if (m_type == ENTER)
	{
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	return h;
}

//==========================================
//  �I������
//==========================================
void CLogo::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo::Update(void)
{
	//�G���^�[��_�ł���
	if (m_type == ENTER)
	{
		m_fCounter += 0.02f;
		float fAlpha = sinf(m_fCounter) * 0.5f + 0.5f;
		D3DXCOLOR col = GetCol();
		col.a = fAlpha;
		SetCol(col);
	}

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	//�C���X�^���X����
	CLogo *pLogo = NULL;

	//NULL�`�F�b�N
	if (pLogo == NULL)
	{
		//���������m��
		pLogo = new CLogo;
	}

	//�l�����蓖�Ă�
	pLogo->m_pos = pos;
	pLogo->m_size = size;
	pLogo->m_type = type;

	//�e�N�X�`�������蓖�Ă�
	switch (type)
	{
	case TITLE:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::TITLE));
		break;

	case RESULT:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::RESULT));
		break;

	case RANKING:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::RANKING));
		break;

	case ENTER:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::ENTER));
		break;

	case RANK:

		pLogo->BindTexture(CManager::GetTexture()->GetAddress(CTexture::RANK));
		break;

	}

	//������
	if (pLogo != NULL)
	{
		pLogo->Init();
	}

	//�|�C���^��Ԃ�
	return pLogo;
}
