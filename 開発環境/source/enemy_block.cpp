//==========================================
//
//  壁役(enemy_block.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_block.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CEnemy_Block::mc_fBlock = 300.0f;

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Block::CEnemy_Block(int nPriority) : CEnemy(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Block::~CEnemy_Block()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Block::Init(void)
{
	//タイプの設定
	SetType(CObject::TYPE_BLOCK_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::BLOCK_LAYER);

	//モデル用のメモリの確保
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

	//モーション情報の生成
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}

	CEnemy::Init();

	//初期位置を保存する
	m_posDef = m_pos;

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Block::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Block::Update(void)
{
	//弾にならない限り位置を固定する
	if (this->GetType() != TYPE_BULLET_ENEMY)
	{
		m_pos = m_posDef;
	}

	//プレイヤーを向く
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;
	m_rot.y = atan2f(-vecToPlayer.x, -vecToPlayer.z);

	//ブロック
	Block();

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Block::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  敵を止める処理
//==========================================
void CEnemy_Block::Block(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//自分のアドレスを取得
		CObject *pObj = this->GetNext();

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_BULLET_ENEMY && pObj != this) //敵の場合
			{
				//現在の敵と自分を結ぶベクトルを取得する
				D3DXVECTOR3 posObj = pObj->GetPos();
				D3DXVECTOR3 vecToObj = m_pos - posObj;

				//ベクトルの大きさを算出
				float fLength = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);

				//接触範囲内にいた場合
				if (fLength < mc_fBlock * mc_fBlock)
				{
					pObj->SetType(TYPE_NORMAL_ENEMY);
					pObj->SetPos(pObj->GetOldPos());
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}

}
