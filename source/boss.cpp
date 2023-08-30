//==========================================
//
//  ボスクラス(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "model.h"
#include "renderer.h"
#include "particle.h"

//==========================================
//  コンストラクタ
//==========================================
CBoss::CBoss()
{

}

//==========================================
//  デストラクタ
//==========================================
CBoss::~CBoss()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBoss::Init(void)
{
	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS_LAYER);

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

	//エネミータグを上書き
	SetType(CObject::TYPE_BOSS);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBoss::Uninit(void)
{
	//パーティクルを発生
	D3DXVECTOR3 color = D3DXVECTOR3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	CParticle::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(color.x, color.y, color.z, 1.0f), 50, 50, 50, 50);
	CParticle::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(color.z, color.x, color.y, 1.0f), 50, 50, 50, 50);
	CParticle::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(color.y, color.z, color.x, 1.0f), 50, 50, 50, 50);

	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBoss::Update(void)
{
	//回転
	Rotate();

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CBoss::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CEnemy::Draw();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  回転処理
//==========================================
void CBoss::Rotate()
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//プレイヤーに向くベクトルを算出
	D3DXVECTOR3 vecToPlayer = m_pos - posPlayer;

	//ベクトルの角度を算出
	float fAngle = atan2f(vecToPlayer.x, vecToPlayer.z);

	//角度を適用
	m_rot.y = fAngle;
}
