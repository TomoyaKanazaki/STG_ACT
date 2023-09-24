//==========================================
//
//  ���U���g�}�l�[�W��(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "input.h"
#include "logo.h"
#include "bg.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CResultManager::CResultManager()
{
	m_nCntScene = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CResultManager::~CResultManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CResultManager::Init(void)
{
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.2f, 0.0f), CLogo::RESULT);

	//�w�i�̐���
	CBg::Create();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CResultManager::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CResultManager::Update(void)
{
	//�V�[���o�ߎ��Ԃ����Z
	m_nCntScene++;

	//��ʑJ��
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || m_nCntScene >= 600)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RANKING);
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CResultManager::Draw(void)
{

}
