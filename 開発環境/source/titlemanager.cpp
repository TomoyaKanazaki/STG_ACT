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
#include "logo.h"
#include "camera.h"
#include "light.h"
#include "bg.h"
#include "camera_title.h"
#include "debris.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CLight *CTitleManager::m_pLight = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CTitleManager::CTitleManager()
{
	m_nCntScene = 0;
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
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.2f, 0.0f), CLogo::TITLE);

	//�w�i�̐���
	CBg::Create();

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//���݂̐���
	for (int nCnt = 0; nCnt < 100; nCnt++)
	{
		CDebris::Create();
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTitleManager::Uninit(void)
{
	//���C�g�̏I���A�j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
}

//==========================================
//  �X�V����
//==========================================
void CTitleManager::Update(void)
{
	//�V�[���o�ߎ��Ԃ����Z
	m_nCntScene++;

	//��ʑJ��
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		return;
	}
	else if (m_nCntScene >= 900)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RANKING);
		return;
	}

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CTitleManager::Draw(void)
{

}
