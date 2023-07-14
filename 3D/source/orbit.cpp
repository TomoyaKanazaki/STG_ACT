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

//==========================================
//  コンストラクタ
//==========================================
COrbit::COrbit()
{
	m_parent = NULL;
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_nLife = 0;
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_nLife > 0)
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer
		(
			sizeof(VERTEX_3D) * m_nNumVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL
		);

		//頂点バッファの呼び出し
		VERTEX_3D *pVtx;

		//頂点バッファのロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点情報を初期化
		for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
		{
			//頂点座標の設定
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//法線ベクトルの設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCntVtx].col = m_Col;

			//テクスチャ座標の設定
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void COrbit::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void COrbit::Update(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 *pOldPos = new D3DXVECTOR3[m_nNumVtx - 2];

	//親の取得
	D3DXMATRIX mtxWorld, mtxRot, mtxTrans;
	m_rot = m_parent->GetRot();
	m_pos = m_parent->GetPos();

	////ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&m_mtxWorld);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//前回位置を保存
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx - 2; nCntVtx++)
	{
		pOldPos[nCntVtx] = pVtx[nCntVtx].pos;
	}

	//最新の頂点位置を設定
	pVtx[0].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.y) * m_fLength,
		m_pos.y,
		m_pos.z + cosf(m_rot.y) * m_fLength
	);
	pVtx[1].pos = m_pos;

	//頂点座標をずらす
	for (int nCntVtx = 2; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		pVtx[nCntVtx].pos = pOldPos[nCntVtx - 2];
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	//メモリを開放
	delete[] pOldPos;
}

//==========================================
//  描画処理
//==========================================
void COrbit::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//カリングを無効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,
		0,
		m_nNumVtx - 2
	);

	//カリングを有効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
COrbit *COrbit::Create(CModel *pParent, D3DXCOLOR col, float fLength, int nLife)
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
	pOrbit->m_Col = col;
	pOrbit->m_fLength = fLength;
	pOrbit->m_nLife = nLife;
	pOrbit->m_nNumVtx = pOrbit->m_nLife * 2;

	//初期化
	pOrbit->Init();

	//ポインタを返す
	return pOrbit;
}
