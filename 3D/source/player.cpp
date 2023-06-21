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
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "field.h"
#include "object_mesh.h"

//==========================================
//  マクロ定義
//==========================================
#define PLAYER_SPEED (1.0f) //プレイヤーの移動速度(キーボード)

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 0.0f;
	m_fAngle = 0.0f;
	m_apModel[0] = NULL;
	m_apModel[1] = NULL;
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

	//実体を生成
	m_apModel[0] = CModel::Create(m_pos, m_size, m_rot, 1);
	m_apModel[1] = CModel::Create(m_pos, m_size, m_rot, 0, m_apModel[0]);

	//影を生成
	//m_pShadow = CShadow::Create(m_pos, m_size, m_rot);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	//前回座標の保存
	D3DXVECTOR3 oldpos = m_pos;

	//存在位置の判定
	if (CManager::GetMesh()->OnMesh(m_pos) == false)
	{
		//デバッグ表示
		CManager::GetDebugProc()->Print("\n\n\n外に出てる!");
	}

	//移動処理
	Move();

	//回転処理
	if (oldpos != m_pos)
	{
		Rotate();
	}

	//高さを取得する
	m_pos.y = CManager::GetField()->GetHeight(m_pos);

	//実体に情報を与える
	m_apModel[0]->SetTransform(m_pos, m_rot);

	//エフェクトを呼び出す
	//CEffect::Create(m_pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), m_rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100);

	//影の情報を更新する
	//m_pShadow->SetTransform(m_pos, m_rot);

	//デバッグ表示
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
