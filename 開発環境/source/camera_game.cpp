//==========================================
//
//  カメラゲームクラス(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "manager.h"
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

//==========================================
//  一人称視点の操作
//==========================================
void CCameraGame::FirstPerson(void)
{
	//視点の値を更新
	m_rot += CManager::GetMouse()->GetMouseMove();

	//角度の補正
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//角度を更新
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.x)) * CAMERA_DISTANCE;
	m_posR.y = m_posV.y - cosf(m_rot.z) * CAMERA_DISTANCE;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * CAMERA_DISTANCE;
}

//==========================================
//  三人称視点の操作
//==========================================
void CCameraGame::ThirdPerson(void)
{
	//注視点を更新
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//視点の値を更新
	m_rot.y += CManager::GetMouse()->GetMouseMove().x;

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//視点を更新
	m_posV.x = posPlayer.x + (sinf(m_rot.y) * CAMERA_DISTANCE);
	m_posV.y = posPlayer.y + HEIGHT;
	m_posV.z = posPlayer.z + (cosf(m_rot.y) * CAMERA_DISTANCE);

	//注視点を更新
	m_posR.x = posPlayer.x - (sinf(m_rot.y) * CAMERA_DISTANCE);
	m_posR.y = posPlayer.y;
	m_posR.z = posPlayer.z - (cosf(m_rot.y) * CAMERA_DISTANCE);
}

//==========================================
//  移動
//==========================================
void CCameraGame::Move(void)
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//プレイヤーにカメラを追従させる
	m_posV = pos;
	m_posR = pos;

	//プレイヤーからカメラを離す
	m_posV += m_diff;
	m_posR -= m_diff;
	m_posR.y = pos.y;
}
