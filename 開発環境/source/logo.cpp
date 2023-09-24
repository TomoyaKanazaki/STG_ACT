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
	CObject2D::Init();

	return S_OK;
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

	}

	//������
	if (pLogo != NULL)
	{
		pLogo->Init();
	}

	//�|�C���^��Ԃ�
	return pLogo;
}
