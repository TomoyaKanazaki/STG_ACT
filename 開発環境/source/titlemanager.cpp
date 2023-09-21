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

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CCamera *CTitleManager::m_pCamera = NULL;
CLight *CTitleManager::m_pLight = NULL;

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
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, 0.0f), CLogo::TITLE);

	//�w�i�̐���
	CBg::Create();

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTitleManager::Uninit(void)
{
	//�J�����̏I���A�j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

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
	//��ʑJ�ڃe�X�g
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CTitleManager::Draw(void)
{

}
