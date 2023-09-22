//==========================================
//
//  �����L���O�}�l�[�W��(rankingmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "rankingmanager.h"
#include "logo.h"
#include "bg.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CRankingManager::CRankingManager()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CRankingManager::~CRankingManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CRankingManager::Init(void)
{
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.2f, 0.0f), CLogo::RESULT);

	//�w�i�̐���
	CBg::Create();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CRankingManager::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CRankingManager::Update(void)
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
void CRankingManager::Draw(void)
{

}
