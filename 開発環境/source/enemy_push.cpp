//==========================================
//
//  押し出しの敵(enemy_push.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_push.h"
#include "gamemanager.h"
#include "player.h"
#include "model.h"
#include "motion.h"
#include "effect.h"
#include "manager.h"
#include "debugproc.h"
#include "object_fan.h"
#include "sound.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CEnemy_Push::mc_fPush = 400.0f;

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Push::CEnemy_Push(int nPriority) : CEnemy(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Push::~CEnemy_Push()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Push::Init(void)
{
	//タイプの設定
	SetType(CObject::TYPE_NORMAL_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PUSH_LAYER);

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

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Push::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Push::Update(void)
{
	//角度を更新
	D3DXVECTOR3 rotModel = m_ppModel[1]->GetRot();
	rotModel.y += 0.1f;

	//角度の補正
	if (rotModel.y > D3DX_PI)
	{
		rotModel.y = -D3DX_PI;
	}
	if (rotModel.y < -D3DX_PI)
	{
		rotModel.y = D3DX_PI;
	}

	//エフェクトを出す
	if (this->GetType() != CObject::TYPE_BULLET_ENEMY)
	{
		D3DXVECTOR3 posEffect = D3DXVECTOR3(m_pos.x + (sinf(rotModel.y) * mc_fPush), 30.0f, m_pos.z + (cosf(rotModel.y) * mc_fPush));
		CEffect::Create(posEffect, m_size * 0.5f, D3DXCOLOR(0.2f, 0.7f, 0.8f, 1.0f), 100);
	}

	//角度を適用
	m_ppModel[1]->SetRot(rotModel);

	//床から落ちる
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
	}

	Target();
	Push();
	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Push::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  弾く処理
//==========================================
void CEnemy_Push::Push(void)
{
	//プレイヤーの位置を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//プレイヤーまでの距離を判定
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;
	vecToPlayer.y = 0.0f;
	float fLength = (vecToPlayer.x * vecToPlayer.x) + (vecToPlayer.z * vecToPlayer.z);

	//接触判定
	if (mc_fPush * mc_fPush >= fLength)
	{
		CManager::GetSound()->Play(CSound::SOUND_LABEL_PUSH);

		CGameManager::GetPlayer()->SetMove(vecToPlayer * 0.5f);
	}
}

//==========================================
//  プレイヤーを見る
//==========================================
void CEnemy_Push::Target(void)
{
	//プレイヤーの座用を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//プレイヤーに向かうベクトルを算出
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//プレイヤーの方向を向く
	float fRot = atan2f(-vecToPlayer.x, -vecToPlayer.z);
	m_rot.y = fRot;
}
