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

//==========================================
//  �R���X�g���N�^
//==========================================
CResultManager::CResultManager()
{

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
#if _DEBUG
	//��ʑJ�ڃe�X�g
	if (CManager::GetKeyboard()->GetTrigger(DIK_0))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		return;
	}
#endif
}

//==========================================
//  �`�揈��
//==========================================
void CResultManager::Draw(void)
{

}
