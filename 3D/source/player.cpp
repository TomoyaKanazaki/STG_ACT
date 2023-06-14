//==========================================
//
//  プレイヤークラス(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "effect.h"
#include "sound.h"
#include "debugproc.h"
#include "object_x.h"
#include "camera.h"

//==========================================
//  マクロ定義
//==========================================
#define PLAYER_SPEED (1.0f) //プレイヤーの移動速度(キーボード)

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 0.0f;
	m_fAngle = 0.0f;
	body = NULL;
}

//==========================================
//  デストラクタ
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CPlayer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//各種情報の保存
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//タイプの設定
	SetType(TYPE_PLAYER);

	//モデルを生成する
	body = CObject_X::Create(m_pos, m_size, m_rot);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	//前回座標の保存
	D3DXVECTOR3 oldpos = m_pos;

	//移動処理
	Move();

	//回転処理
	if (oldpos != m_pos)
	{
		Rotate();
	}

	//モデルに情報を与える
	body->SetTransform(m_pos, m_rot);

	//エフェクトを呼び出す
	CEffect::Create(m_pos, D3DXVECTOR3(30.0f, 0.0f, 30.0f), m_rot, D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f), 30);

	CManager::GetDebugProc()->Print("\n\n\nプレイヤー座標 : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("プレイヤー方向 : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("プレイヤー移動量 : ( %f, %f, %f )\n", m_move.x, m_move.y, m_move.z);
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw()
{

}

//==========================================
//  オブジェクト生成処理
//==========================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CPlayer *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{
		//メモリを確保
		pPlayer = new CPlayer;
	}

	//初期化
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, size, rot);
	}

	//ポインタを返す
	return pPlayer;
}

//==========================================
//  移動処理
//==========================================
void CPlayer::Move(void)
{
	//慣性による移動の停止
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//移動量の取得
	m_move += CManager::GetKeyboard()->GetWASD();

	//移動方向の取得
	m_fAngle = atan2f(m_move.x, m_move.z);

	//移動量の適応
	m_pos += m_move;
}

//==========================================
//  回転処理
//==========================================
void CPlayer::Rotate(void)
{
	float fRotMove, fRotDest, fRotDiff;

	//現在の角度と目的の角度の差分を計算
	fRotMove = m_rot.y;
	fRotDest = m_fAngle;
	fRotDiff = fRotDest - fRotMove;

	//角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	//方向転換の慣性
	fRotMove += fRotDiff * 0.2f;

	//角度の補正
	if (fRotMove > D3DX_PI)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove <= -D3DX_PI)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	//方向を適用する
	m_rot.y = fRotMove;

	m_fAngle = m_rot.y;
}
