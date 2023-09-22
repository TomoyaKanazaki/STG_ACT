//==========================================
//
//  ���Z����^�C�}�[�̃N���X(timer_sab.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "precompile.h"
#include "timer_sab.h"
#include "manager.h"
#include "scenemanager.h"
#include "debugproc.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTimer_Sab::CTimer_Sab(int nPriority) : CTime(nPriority)
{
	m_nProgress = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTimer_Sab::~CTimer_Sab()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTimer_Sab::Init(void)
{
	//�����l����
	m_nCurrent = m_nMax;

	return CTime::Init();
}

//==========================================
//  �I������
//==========================================
void CTimer_Sab::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CTimer_Sab::Update(void)
{
	//�������ԂőJ�ڂ���
	if (m_nCurrent <= 0)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	//�o�ߎ��Ԃ����Z
	m_nProgress++;

	//���ݎ������v�Z
	m_nCurrent = m_nMax - (m_nProgress / 60);

	CManager::GetDebugProc()->Print("�c�莞�� : %d\n", m_nCurrent);

	CTime::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTimer_Sab::Draw(void)
{

}
