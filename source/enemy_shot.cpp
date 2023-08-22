//==========================================
//
//  弾を撃つ敵のクラス(enemy_shot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_shot.h"
#include "gamemanager.h"
#include "player.h"
#include "bullet.h"
#include "manager.h"
#include "input.h"

//==========================================
//  マクロ定義
//==========================================
#define SPEED (3.0f) //弾の速度

//==========================================
//  コンストラクタ
//==========================================
CEnemyShot::CEnemyShot()
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyShot::~CEnemyShot()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyShot::Init(void)
{
	CEnemy::Init();
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyShot::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyShot::Update(void)
{
	Shot();
	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemyShot::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  弾を撃つ処理
//==========================================
void CEnemyShot::Shot(void)
{
	//プレイヤーの位置を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//自分からプレイヤーに向けたベクトルを算出
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//算出したベクトルから角度を算出
	float rotVector = atan2f(vecToPlayer.x, vecToPlayer.z);

	//算出した角度を自分の方向にする
	m_rot.y = rotVector;

	//算出したベクトルを正規化する
	vecToPlayer.y = 0.0f;
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//プレイヤーへのベクトルに倍率与える
	vecToPlayer *= SPEED;

	//高さを与える
	D3DXVECTOR3 pos = m_pos;
	pos.y += 10.0f;

	//弾を撃つ
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CBullet::Create(pos, D3DXVECTOR3(25.0f, 25.0f, 0.0f), vecToPlayer, CBullet::ENEMY, CBullet::NORMAL_BULLET);
	}
}
