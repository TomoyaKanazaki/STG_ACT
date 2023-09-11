//==========================================
//
//  �A�j���[�V����3D�N���X(object3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object3D_Anim.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CObject3D_Anim::CObject3D_Anim(int nPriority) : CObject3D(nPriority)
{
	m_Type = TYPE_NONE;
	m_nNumPattern = 0;
	m_nAnimPattern = 0;
	m_nAnimCounter = 0;
	m_nUpdateFrame = 0;
	m_bLoop = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject3D_Anim::~CObject3D_Anim()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject3D_Anim::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//�e�N�X�`�����W��ݒ�
	SetTexPos();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject3D_Anim::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CObject3D_Anim::Update(void)
{
	//�J�E���^�[�̍X�V
	m_nAnimCounter++;

	//�A�j���[�V�����̍X�V
	if (m_nAnimCounter % m_nUpdateFrame == 0)
	{
		if (FAILED(SetTexPos()))
		{
			this->Release();
			return;
		}
	}

	//�X�V����
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CObject3D_Anim::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  �A�j���[�V�������̐ݒ�
//==========================================
void CObject3D_Anim::SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type)
{
	m_nNumPattern = nPattern;
	m_nUpdateFrame = nInterval;
	m_bLoop = bLoop;
	m_Type = type;
}

//==========================================
//  �e�N�X�`���̐ݒ�
//==========================================
HRESULT CObject3D_Anim::SetTexPos(void)
{
	//���[�J���ϐ��錾
	float fUVPos;
	D3DXVECTOR2 min, max;

	//�e�N�X�`�����W�̍ŏ��l���Z�o����
	fUVPos = (1.0f / m_nNumPattern) * m_nAnimPattern;

	//�l��K������
	switch (CObject3D_Anim::m_Type)
	{
	case TYPE_U:
		min = D3DXVECTOR2(fUVPos, 0.0f);
		break;
	case TYPE_V:
		min = D3DXVECTOR2(0.0f, fUVPos);
		break;
	default:
		break;
	}

	//�e�N�X�`�����W�̍ő�l���Z�o����
	if (this->GetType() == CObject::TYPE_BG)
	{
		fUVPos += 1.0f;
	}
	else
	{
		fUVPos = (1.0f / m_nNumPattern) * (m_nAnimPattern + 1);
	}

	//�l��K������
	switch (CObject3D_Anim::m_Type)
	{
	case TYPE_U:
		max = D3DXVECTOR2(fUVPos, 1.0f);
		break;
	case TYPE_V:
		max = D3DXVECTOR2(1.0f, fUVPos);
		break;
	default:
		break;
	}

	//�e�N�X�`�����W�̍X�V
	SetTex(min, max);

	if (m_nAnimPattern >= m_nNumPattern) //�Ō�̃A�j���[�V�����̏ꍇ
	{
		if (m_bLoop) //���[�v����ꍇ
		{
			m_nAnimPattern = 0;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		//�A�j���[�V�����ԍ����X�V����
		m_nAnimPattern++;
	}

	return S_OK;
}
