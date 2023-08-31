//==========================================
//
//  �i���o�[�N���X(number.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{
	m_nNumber = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CNumber::~CNumber()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CNumber::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_NUMBER);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CNumber::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CNumber::Update(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR2 min, max;

	//�\������l�Ƀe�N�X�`�����W�����킹��
	min = D3DXVECTOR2(m_nNumber * 0.1f, 0.0f);
	max = D3DXVECTOR2(min.x + 0.1f, 1.0f);

	//�e�N�X�`�����W�����蓖�Ă�
	SetTex(min, max);
}

//==========================================
//  �`�揈��
//==========================================
void CNumber::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CNumber * CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nNumber)
{
	//�C���X�^���X����
	CNumber *pNumber = NULL;

	//NULL�`�F�b�N
	if (pNumber == NULL)
	{
		//���������m��
		pNumber = new CNumber;
	}

	//�l�����蓖�Ă�
	pNumber->m_nNumber = nNumber;
	pNumber->m_pos = pos;
	pNumber->m_size = size;
	pNumber->m_rot = rot;

	//������
	if (pNumber != NULL)
	{
		pNumber->Init();
	}

	//�e�N�X�`�������蓖�Ă�
	pNumber->BindTexture(CManager::GetTexture()->GetAddress(CTexture::NUMBER));

	//�|�C���^��Ԃ�
	return pNumber;
}
