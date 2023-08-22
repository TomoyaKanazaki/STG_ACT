//==========================================
//
//  �o�b�e���[�N���X(battery.cpp)
//  Author ; Tomoya Kanazaki
//
//==========================================
#include "battery.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CBattery::mc_fMax = 1000.0f; //�ő�l
const float CBattery::mc_fTime = 120.0f; //��������
const float CBattery::mc_fSab = (CBattery::mc_fMax / (CBattery::mc_fTime * 60.0f)); //��������

//==========================================
//  �R���X�g���N�^
//==========================================
CBattery::CBattery(int nPriority) : CObject2D(nPriority)
{
	m_fBattery = mc_fMax;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBattery::~CBattery()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBattery::Init(void)
{
	//�e��l��ݒ�
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 680.0f, 0.0f);
	m_size = D3DXVECTOR3(m_fBattery, 40.0f, 0.0f);

	//���̂̏�����
	CObject2D::Init();

	//�l��Ԃ�
	return S_OK;
}

//==========================================
//  �I������
//=========================================
void CBattery::Uninit(void)
{
	//���̂̏I��
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBattery::Update(void)
{
	//��Ɍ�����������o�b�e���[
	m_fBattery -= mc_fSab;

	//0����������ꍇ�␳
	if (m_fBattery <= 0)
	{
		m_fBattery = 0;
	}

	CManager::GetDebugProc()->Print("�o�b�e���[�ő�l : %f\n", mc_fMax);
	CManager::GetDebugProc()->Print("�o�b�e���[������ : %f\n", mc_fSab);
	CManager::GetDebugProc()->Print("�o�b�e���[���ݒl : %f\n", m_fBattery);

	//���݂̒l���Q�[�W�̒����ɔ��f
	m_size.x = m_fBattery;

	//���̂̍X�V
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBattery::Draw(void)
{
	//���̂̕`��
	CObject2D::Draw();
}

//==========================================
//  ���Z����
//==========================================
void CBattery::Add(const float fAdd)
{
	//�ő�l�����̏ꍇ���Z�\
	if (m_fBattery < mc_fMax)
	{
		//���Z
		m_fBattery += fAdd;

		//�ő�l�𒴂����ꍇ�␳����
		if (m_fBattery > mc_fMax)
		{
			m_fBattery = mc_fMax;
		}
	}
}

//==========================================
//  ���Z����
//==========================================
void CBattery::Sab(const float fSab)
{
	//0�ȏ�̏ꍇ���Z�\
	if (0 < m_fBattery)
	{
		//���Z
		m_fBattery -= fSab;

		//0����������ꍇ�␳
		if (m_fBattery <= 0)
		{
			m_fBattery = 0;
		}
	}
}

//==========================================
//  ��������
//==========================================
CBattery *CBattery::Create()
{
	//�C���X�^���X����
	CBattery *pBattery = NULL;

	//���������m��
	pBattery = new CBattery;

	//������
	pBattery->Init();

	//�|�C���^��Ԃ�
	return pBattery;
}
