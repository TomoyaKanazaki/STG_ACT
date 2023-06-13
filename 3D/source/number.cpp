//==========================================
//
//  �i���o�[�N���X(number.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "number.h"
#include "manager.h"
#include "renderer.h"

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
HRESULT CNumber::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
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
//  �ǂݍ��ݏ���
//==========================================
HRESULT CNumber::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  �e�N�X�`���j��
//==========================================
void CNumber::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
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

	//������
	if (pNumber != NULL)
	{
		pNumber->Init(pos, size, rot);
	}

	//�e�N�X�`�������蓖�Ă�
	pNumber->BindTexture(m_pTexture);

	//�|�C���^��Ԃ�
	return pNumber;
}
