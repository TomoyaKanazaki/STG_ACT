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
	m_pVtxBuff = NULL;
	m_nLife = 0;
	m_nNumVtx = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_offset[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_offset[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_offset[nCnt].mtxWorld = {};
	}
	m_mtxWorld = {};
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
	m_nNumVtx = m_nLife * 2;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_offset[nCnt].mtxWorld);
	}

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
			pVtx[nCntVtx].pos = D3DXVECTOR3(m_offset[0].mtxWorld._41, m_offset[0].mtxWorld._42, m_offset[0].mtxWorld._43);

			//法線ベクトルの設定
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCntVtx].col = m_colDef;

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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_offset[nCnt].mtxWorld);
	}

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//一時保存用変数
	D3DXVECTOR3 *oldpos = new D3DXVECTOR3[m_nNumVtx];
	D3DXCOLOR *oldcol = new D3DXCOLOR[m_nNumVtx];

	//前回情報を保存する
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		oldpos[nCnt] = pVtx[nCnt].pos;
		oldcol[nCnt] = pVtx[nCnt].col;
	}

	//頂点情報をずらす
	for (int nCnt = 2; nCnt < m_nNumVtx; nCnt++)
	{
		pVtx[nCnt].pos = oldpos[nCnt - 2];
		pVtx[nCnt].col = oldcol[nCnt - 2];
	}

	//メモリを開放
	delete[] oldpos;
	delete[] oldcol;

	//最新の情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_offset[0].mtxWorld._41, m_offset[0].mtxWorld._42, m_offset[0].mtxWorld._43);
	pVtx[0].col = m_offset[0].col;
	pVtx[1].pos = D3DXVECTOR3(m_offset[1].mtxWorld._41, m_offset[1].mtxWorld._42, m_offset[1].mtxWorld._43);
	pVtx[1].col = m_offset[1].col;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		CManager::GetDebugProc()->Print("軌跡座標 : ( %f, %f, %f )\n", pVtx[nCnt].pos.x, pVtx[nCnt].pos.y, pVtx[nCnt].pos.z);
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  描画処理
//==========================================
void COrbit::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カリングを無効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//親マトリックスの設定
	D3DXMATRIX mtxParent = m_parent->GetMtx();

	//ワールドマトリックスと親マトリックスをかけ合わせる
	D3DXMatrixMultiply
	(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent
	);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumVtx - 2);

	//カリングを有効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
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
