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
//  狙われる処理
//==========================================
void CEnemyShot::Targeted(void)
{
	//内部判定フラグ
	bool bIn = false;

	//カーソル位置を取得する
	D3DXVECTOR3 posTarget = CGameManager::GetTarget()->GetPos();

	//カーソルまでの距離を判定
	float fLength =
		(posTarget.x - m_pos.x) * (posTarget.x - m_pos.x) + (posTarget.z - m_pos.z) * (posTarget.z - m_pos.z);

	//範囲内の判定
	if (CGameManager::GetTarget()->GetSize().x * CGameManager::GetTarget()->GetSize().x * 0.64f > fLength)
	{
		if (m_pRockon == NULL)
		{
			m_pRockon = CRockon::Create(m_pos);
		}
		bIn = true;
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
