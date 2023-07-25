//==========================================
//
//  �t�F�[�h�N���X(fade.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "fade.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	m_bFinish = false;
	m_nTime = 0;
	m_nCounter = 0;
	m_fAlpha = 0.0f;
	m_Mode = MODE_NONE;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CFade::~CFade()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CFade::Init(void)
{
	//�|���S���̏���ݒ�
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	m_size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//�^�C�v�̐ݒ�
	SetType(TYPE_FADE);

	//�J���[�̏���ݒ�
	switch (m_Mode)
	{
	case MODE_IN:
		SetCol(D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f));
		break;
	case MODE_OUT:
		SetCol(D3DXCOLOR(0.0f, 0.5f, 0.5f, 0.0f));
		break;
	default:
		break;
	}

	//���ߒ萔��ݒ�
	m_fAlpha = 1.0f / (float)m_nTime;
	if (m_Mode == MODE_IN)
	{
		m_fAlpha *= -1.0f;
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CFade::Update(void)
{
	//���݂̕s�����x���擾
	float fAlpha = GetCol().a;

	//�I���t���O�𗧂Ă�
	if (m_nCounter >= m_nTime && (fAlpha >= 1.0f || 0.0f >= fAlpha))
	{
		m_bFinish = true;
		return;
	}

	//�s�����x��ݒ�
	AddAlpah(m_fAlpha);

	//�J�E���^�[�����Z
	m_nCounter++;

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("�����x : %f\n", fAlpha);
}

//==========================================
//  �`�揈��
//==========================================
void CFade::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CFade * CFade::Create(int nTime, MODE mode)
{
	//�C���X�^���X����
	CFade *pFade = NULL;

	//NULL�`�F�b�N
	if (pFade == NULL)
	{
		//���������m��
		pFade = new CFade;
	}

	//�l�����蓖�Ă�
	pFade->m_nTime = nTime;
	pFade->m_Mode = mode;

	//������
	if (pFade != NULL)
	{
		pFade->Init();
	}

	//�|�C���^��Ԃ�
	return pFade;
}
