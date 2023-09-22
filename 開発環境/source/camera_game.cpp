//==========================================
//
//  カメラゲームクラス(camera_game.cpp)
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
//  コンストラクタ
//==========================================
CCameraGame::CCameraGame()
{

}

//==========================================
//  デストラクタ
//==========================================
CCameraGame::~CCameraGame()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCameraGame::Init(void)
{
	//注視点を設定
	m_posR = CGameManager::GetPlayer()->GetPos();
	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraGame::Update(void)
{
	//視点操作
	ThirdPerson();

	CCamera::Update();
}
