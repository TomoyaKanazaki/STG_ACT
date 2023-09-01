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
#include "model.h"
#include "motion.h"
#include "manager.h"
#include "camera.h"
#include "target.h"
#include "rockon.h"

//==========================================
//  マクロ定義
//==========================================
#define SPEED (3.0f) //弾の速度
#define INTERVAL (60) //弾の発射間隔

//==========================================
//  コンストラクタ
//==========================================
CEnemyShot::CEnemyShot()
{
	m_nInterval = 0;
	m_pRockon = NULL;
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
	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_SHOT_LAYER);

	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//必要なモデルを生成
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//空にする
		m_ppModel[nCnt] = NULL;

		//親が存在しない場合
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	CEnemy::Init();
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemyShot::Uninit(void)
{
	if (m_pRockon != NULL)
	{
		m_pRockon->Uninit();
	}
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyShot::Update(void)
{
	//弾の発射時間を更新
	m_nInterval++;

	//弾の発射に関する処理
	Shot();

	//狙われろ
	Targeted();

	//モーションを更新する
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}

	//更新
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
	float rotVector = atan2f(vecToPlayer.z, -vecToPlayer.x);

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
	if (m_nInterval % INTERVAL == 0)
	{
		CBullet::Create(pos, D3DXVECTOR3(25.0f, 25.0f, 0.0f), vecToPlayer, CBullet::ENEMY, CBullet::NORMAL_BULLET);
	}
}

//==========================================
//  狙われる処理
//==========================================
void CEnemyShot::Targeted(void)
{
	//内部判定フラグ
	bool bIn = false;

	//ビューポートの設定
	D3DVIEWPORT9 vp = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };

	//計算用変数宣言
	D3DXMATRIX mtxView = CGameManager::GetCamera()->CreateViewMatrix(); //ビューマトリックス
	D3DXMATRIX mtxWorld; //ワールドマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//敵のスクリーン座標を算出
	D3DXVECTOR3 screenPos;
	D3DXMATRIX mtxProjection = CGameManager::GetCamera()->GetMtxPro();
	D3DXVec3Project
	(
		&screenPos,
		&m_pos,
		&vp,
		&mtxProjection,
		&mtxView,
		&mtxWorld
	);

	//範囲内の判定
	if (screenPos.x < CGameManager::GetTarget()->GetPos().x + CGameManager::GetTarget()->GetSize().x * 0.5f && !bIn)
	{
		if (screenPos.x > CGameManager::GetTarget()->GetPos().x - CGameManager::GetTarget()->GetSize().x * 0.5f && !bIn)
		{
			if (screenPos.y < CGameManager::GetTarget()->GetPos().y + CGameManager::GetTarget()->GetSize().y * 0.5f && !bIn)
			{
				if (screenPos.y > CGameManager::GetTarget()->GetPos().y - CGameManager::GetTarget()->GetSize().y * 0.5f && !bIn)
				{
					if (m_pRockon == NULL)
					{
						m_pRockon = CRockon::Create(m_pos);
					}
					bIn = true;
				}
			}
		}
	}

	if(!bIn)
	{
		if (m_pRockon != NULL)
		{
			m_pRockon->Uninit();
			m_pRockon = NULL;
		}
	}
}
