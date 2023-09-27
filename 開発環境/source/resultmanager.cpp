//==========================================
//
//  ���U���g�}�l�[�W��(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "scenemanager.h"
#include "input.h"
#include "logo.h"
#include "bg.h"
#include "debris.h"
#include "ranking.h"
#include "rank.h"
#include "score.h"
#include "sound.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CResultManager::CResultManager()
{
	m_nCntScene = 0;
	m_nRank = 0;
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
	//RESULT�̕\��
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.1f, 0.0f), CLogo::RESULT);

	//����̏��ʂ̕\��
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.35f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.1f, 0.0f), CLogo::RANK);

	//�X�R�A�̕\��
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.1f, 0.0f), CLogo::RANK);

	//�w�i�̐���
	CBg::Create();

	//���ʂ̎擾
	m_nRank = CRanking::GetRank();
	CRank::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.2f, 0.0f), m_nRank);

	//�X�R�A�̎擾
	CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.85f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CScore::GetScore());

	//���݂̐���
	for (int nCnt = 0; nCnt < 100; nCnt++)
	{
		CDebris::Create();
	}

	//BGM�̍Đ�
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CResultManager::Uninit(void)
{
	//BGM�̒�~
	CManager::GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CResultManager::Update(void)
{
	//�V�[���o�ߎ��Ԃ����Z
	m_nCntScene++;

	//��ʑJ��
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || m_nCntScene >= 1500)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
		return;
	}

	CManager::GetDebugProc()->Print("���� : %d\n", m_nRank);
}

//==========================================
//  �`�揈��
//==========================================
void CResultManager::Draw(void)
{

}
