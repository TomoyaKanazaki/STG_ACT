//==========================================
//
//  軌跡クラス(orbit.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "orbit.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "debugproc.h"
#include "object_mesh.h"
#include "collision.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  マクロ定義
//==========================================
#define WIND_AREA (100.0f) //風圧発生範囲

//==========================================
//  コンストラクタ
//==========================================
COrbit::COrbit()
{
	m_parent = NULL;
	m_nLife = 0;
	m_nNumVtx = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_offset[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_offset[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_offset[nCnt].mtxWorld = {};
	}
	m_pMesh = NULL;
	m_pVtxPos = NULL;
	m_fLength = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
COrbit::~COrbit()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT COrbit::Init(void)
{
	//値の算出
	m_nNumVtx = (m_nLife + 1) * 2;

	//メッシュを生成
	m_pMesh = CObject_Mesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, (float)m_nLife));

	//色を適用
	m_pMesh->SetColor(m_colDef);

	//頂点数分のメモリを確保
	m_pVtxPos = new D3DXVECTOR3[m_nNumVtx];

	//オフセット計算処理
	CalcOffset();

	//プレイヤー中心と端の距離を算出
	D3DXVECTOR3 vecLength = CGameManager::GetPlayer()->GetPos() - m_pVtxPos[1];
	m_fLength = vecLength.x * vecLength.x + vecLength.z * vecLength.z;

	//頂点情報を初期化
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt += 2)
	{
		m_pVtxPos[nCnt] = m_pVtxPos[0];
		m_pVtxPos[nCnt + 1] = m_pVtxPos[1];
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void COrbit::Uninit(void)
{
	//頂点情報を破棄
	delete[] m_pVtxPos;
	m_pVtxPos = NULL;

	//メッシュを破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Uninit();
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void COrbit::Update(void)
{
	//現在の頂点座標を保存
	D3DXVECTOR3 *pOldPos = new D3DXVECTOR3[m_nNumVtx];
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		pOldPos[nCnt] = m_pVtxPos[nCnt];
	}

	//頂点座標を二つずらして保存する
	for (int nCnt = 2; nCnt < m_nNumVtx; nCnt++)
	{
		m_pVtxPos[nCnt] = pOldPos[nCnt - 2];
	}

	//前回の頂点座標を破棄
	delete[] pOldPos;
	pOldPos = NULL;

	//オフセット計算処理
	CalcOffset();

	//頂点座標の適用
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		m_pMesh->SetVtxPos(m_pVtxPos[nCnt], nCnt);
	}

	//先端ポリゴンを生成する頂点の情報
	D3DXVECTOR3 aVtx[4];

	//回転方向計算用変数
	D3DXVECTOR3 Direction;
	D3DXVECTOR3 vtxNew = m_pVtxPos[1] - m_pVtxPos[0];
	D3DXVECTOR3 vtxOld = m_pVtxPos[3] - m_pVtxPos[2];

	//計算用ベクトルの外積を求める
	D3DXVec3Cross(&Direction, &vtxNew, &vtxOld);

	if (Direction.y > 0.0f)
	{
		aVtx[0] = m_pVtxPos[0];
		aVtx[1] = m_pVtxPos[1];
		aVtx[2] = m_pVtxPos[3];
		aVtx[3] = m_pVtxPos[2];
	}
	else if (Direction.y < 0.0f)
	{
		aVtx[0] = m_pVtxPos[2];
		aVtx[1] = m_pVtxPos[3];
		aVtx[2] = m_pVtxPos[1];
		aVtx[3] = m_pVtxPos[0];
	}

	//先端ポリゴンの当たり判定
	Collision::InSquare(&aVtx[0], m_fLength);
}

//==========================================
//  描画処理
//==========================================
void COrbit::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
COrbit *COrbit::Create(CModel *pParent, D3DXCOLOR col, D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, int nLife)
{
	//インスタンス生成
	COrbit *pOrbit = NULL;

	//NULLチェック
	if (pOrbit == NULL)
	{
		//メモリを確保
		pOrbit = new COrbit;
	}

	if (pOrbit == NULL)
	{
		return NULL;
	}

	//値を設定
	pOrbit->m_parent = pParent;
	pOrbit->m_colDef = col;
	pOrbit->m_offset[0].pos = offset0;
	pOrbit->m_offset[1].pos = offset1;
	pOrbit->m_nLife = nLife;

	//初期化
	pOrbit->Init();

	//ポインタを返す
	return pOrbit;
}

//==========================================
//  オフセットの計算処理
//==========================================
void COrbit::CalcOffset(void)
{
	//オフセットの位置を算出
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//ローカル変数宣言
		D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
		D3DXMATRIX mtxParent; //親マトリックス

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_offset[nCnt].mtxWorld);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_offset[nCnt].mtxWorld, &m_offset[nCnt].mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, m_offset[nCnt].pos.x, m_offset[nCnt].pos.y, m_offset[nCnt].pos.z);
		D3DXMatrixMultiply(&m_offset[nCnt].mtxWorld, &m_offset[nCnt].mtxWorld, &mtxTrans);

		//親マトリックスの設定
		mtxParent = m_parent->GetMtx();

		//ワールドマトリックスと親マトリックスをかけ合わせる
		D3DXMatrixMultiply
		(
			&m_offset[nCnt].mtxWorld,
			&m_offset[nCnt].mtxWorld,
			&mtxParent
		);

		//頂点座標を抽出
		m_pVtxPos[nCnt] = D3DXVECTOR3(m_offset[nCnt].mtxWorld._41, m_offset[nCnt].mtxWorld._42, m_offset[nCnt].mtxWorld._43);
	}
}
