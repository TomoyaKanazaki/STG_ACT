//==========================================
//
//  バレットクラス(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "gamemanager.h"
#include "target.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"
#include "object.h"
#include "bullet_normal.h"
#include "bullet_homing.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CBullet::mc_fExplosion = 300.0f;

//==========================================
//  コンストラクタ
//==========================================
CBullet::CBullet(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DefaultPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CBullet::~CBullet()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBullet::Init(void)
{
	m_size = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	SwitchBillboard();

	//タイプの設定
	SetType(TYPE_BULLET);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBullet::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBullet::Update(void)
{
	//移動量を算出
	D3DXVECTOR3 move = m_TargetPos - m_DefaultPos;
	D3DXVECTOR3 ratio = m_pos - m_DefaultPos;
	float fRatio = (ratio.x * ratio.x + ratio.z * ratio.z) / (move.x * move.x + move.z * move.z);
	move.y = 0.0f;
	D3DXVec3Normalize(&move, &move);
	move *= m_fSpeed;
	m_move = move;

	//移動量を適用
	m_pos += m_move;
	m_pos.y = sinf(fRatio * D3DX_PI) * 300.0f + m_DefaultPos.y;

	//エフェクトを呼ぶ
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		//発生するポイント
		D3DXVECTOR3 pos;
		D3DXVec3Lerp(&pos, &m_pos, &m_oldPos, 0.2f * nCnt);
		CEffect::Create(pos, m_size, D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f), 10);
	}

	//消滅条件
	if (m_pos.y < 0.0f)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
		{
			//自分のアドレスを取得
			CObject *pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				//次のアドレスを保存
				CObject *pNext = pObj->GetNext();

				if (pObj->GetType() == CObject::TYPE_ENEMY || pObj->GetType() == CObject::TYPE_BULLET) //敵の場合
				{
					//近くにいるかの判定
					D3DXVECTOR3 vecToObj = m_pos - pObj->GetPos();
					float fLengh = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);
					if (fLengh < mc_fExplosion * mc_fExplosion)
					{
						//殺す
						pObj->Uninit();
					}
				}

				//次のアドレスにずらす
				pObj = pNext;
			}
		}
		Uninit();
		return;
	}

	//更新
	CObject3D::Update();

	CManager::GetDebugProc()->Print("弾の座標 : %f, %f, %f\n", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetDebugProc()->Print("目標までの割合 : %f\n", fRatio);
}

//==========================================
//  描画処理
//==========================================
void CBullet::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画
	CObject3D::Draw();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, float fSpeed)
{
	//インスタンス生成
	CBullet *pBullet = NULL;

	//メモリを確保
	pBullet = new CBullet;

	//値を設定
	pBullet->m_pos = pos;
	pBullet->m_DefaultPos = pos;
	pBullet->m_TargetPos = CGameManager::GetTarget()->GetPos();
	pBullet->m_fSpeed = fSpeed;

	//初期化
	pBullet->Init();

	//テクスチャを割り当てる
	pBullet->BindTexture(CManager::GetTexture()->GetAddress(CTexture::BULLET));

	//ポインタを返す
	return pBullet;
}
