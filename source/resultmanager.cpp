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
	//��ʑJ�ڃe�X�g
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CResultManager::Draw(void)
{

}
