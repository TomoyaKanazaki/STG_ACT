//==========================================
//
//  �^�C�g���}�l�[�W��(titlemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "titlemanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "input.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTitleManager::CTitleManager()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTitleManager::~CTitleManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTitleManager::Init(void)
{
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTitleManager::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CTitleManager::Update(void)
{
#if _DEBUG
	//��ʑJ�ڃe�X�g
	if (CManager::GetKeyboard()->GetTrigger(DIK_0))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		return;
	}
#endif
}

//==========================================
//  �`�揈��
//==========================================
void CTitleManager::Draw(void)
{

}