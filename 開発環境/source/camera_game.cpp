//==========================================
//
//  �J�����Q�[���N���X(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraGame::CCameraGame()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraGame::~CCameraGame()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraGame::Init(void)
{
	//�����_��ݒ�
	m_posR = CGameManager::GetPlayer()->GetPos();
	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraGame::Update(void)
{
	//���_����
	ThirdPerson();

	CCamera::Update();
}
