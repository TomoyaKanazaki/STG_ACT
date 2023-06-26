//==========================================
//
//  メッシュオブジェクトクラス(object_mesh.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_mesh.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CObject_Mesh::CObject_Mesh(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_Mesh.nNumIdx = 0;
	m_Mesh.nNumMesh = 0;
	m_Mesh.nNumMesh_U = 0;
	m_Mesh.nNumMesh_V = 0;
	m_Mesh.nNumVtx = 0;
	m_Mesh.nNumVtx_U = 0;
	m_Mesh.nNumVtx_V = 0;
	m_mtxWorld = {};
}

//==========================================
//  デストラクタ
//==========================================
CObject_Mesh::~CObject_Mesh()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject_Mesh::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//各種変数の初期化
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//頂点生成用変数の設定
	CalcData();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * m_Mesh.nNumMesh,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	//頂点バッファの情報を設定
	SetVtx();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * m_Mesh.nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL
	);

	//インデックスバッファの情報を設定
	SetIdx();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject_Mesh::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CObject_Mesh::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CObject_Mesh::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ワイヤーフレームを有効化
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_Mesh.nNumVtx, //頂点数
		0,
		m_Mesh.nNumMesh //プリミティブ数
	);

	//ワイヤーフレームを無効化
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CObject_Mesh * CObject_Mesh::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv)
{
	//インスタンス生成
	CObject_Mesh *pMesh = NULL;

	//NULLチェック
	if (pMesh == NULL)
	{
		//メモリを確保
		pMesh = new CObject_Mesh;
	}

	if (pMesh == NULL)
	{
		return NULL;
	}

	//分割数を設定
	pMesh->m_Mesh.nNumMesh_U = (int)uv.x;
	pMesh->m_Mesh.nNumMesh_V = (int)uv.y;

	//初期化
	pMesh->Init(pos, size, rot);

	//テクスチャを割り当てる
	pMesh->BindTexture(CManager::GetTexture()->GetAddress(0));

	//ポインタを返す
	return pMesh;
}

//==========================================
//  頂点バッファの設定処理
//==========================================
void CObject_Mesh::SetVtx(void)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_Mesh.nNumVtx; nCntVtx++)
	{
		//法線の設定
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
	}	

	//頂点座標の設定
	for (int nCntVtxU = 0; nCntVtxU < m_Mesh.nNumVtx_U; nCntVtxU++)
	{
		for (int nCntVtxV = 0; nCntVtxV < m_Mesh.nNumVtx_V; nCntVtxV++)
		{
			pVtx[nCntVtxU + (nCntVtxV * m_Mesh.nNumVtx_U)].pos = D3DXVECTOR3
			(
				-(m_size.x * 0.5f) + ((m_size.x / m_Mesh.nNumMesh_U) * nCntVtxU),
				0.0f,
				(m_size.z * 0.5f) - ((m_size.z / m_Mesh.nNumMesh_V) * nCntVtxV)
			);
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  インデックスバッファの設定処理
//==========================================
void CObject_Mesh::SetIdx(void)
{
	//インデックス情報へのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点データの設定
	for (int nCntIdx = 0, nCntTurn = 0, nCntVtx = 0; nCntIdx < m_Mesh.nNumIdx; nCntIdx += 2)
	{
		if (nCntIdx == (2 * ((m_Mesh.nNumVtx_U * nCntTurn) + m_Mesh.nNumVtx_U + nCntTurn))) //折り返し地点
		{
			pIdx[nCntIdx] = pIdx[nCntIdx - 1];
			pIdx[nCntIdx + 1] = nCntVtx + m_Mesh.nNumVtx_U;
			nCntTurn++;
		}
		else //その他
		{
			pIdx[nCntIdx] = nCntVtx + m_Mesh.nNumVtx_U;
			pIdx[nCntIdx + 1] = nCntVtx;
			nCntVtx++;
		}
	}

	//インデックスバッファのアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  各データの計算処理
//==========================================
void CObject_Mesh::CalcData(void)
{
	m_Mesh.nNumVtx_U = m_Mesh.nNumMesh_U + 1;
	m_Mesh.nNumVtx_V = m_Mesh.nNumMesh_V + 1;
	m_Mesh.nNumVtx = m_Mesh.nNumVtx_U * m_Mesh.nNumVtx_V;
	m_Mesh.nNumIdx = (m_Mesh.nNumVtx * 2) - (2 * (abs(m_Mesh.nNumMesh_U - m_Mesh.nNumMesh_V)) + 4);
	m_Mesh.nNumMesh = m_Mesh.nNumIdx - 2;
}

//==========================================
//  メッシュフィールド上の存在判定(判定のみ)
//==========================================
bool CObject_Mesh::OnMesh(const D3DXVECTOR3 pos)
{
	//ローカル変数宣言
	int nCntPoint = 0;

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//上の存在判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		//判定用変数宣言
		float fJudge = (pVtx[nCnt + 1].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[nCnt + 1].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		if (nCnt == m_Mesh.nNumVtx_U - 1)
		{
			fJudge = (pVtx[0].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[0].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		}

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//下の存在判定
	for (int nCnt = m_Mesh.nNumVtx - 1; nCnt > m_Mesh.nNumVtx - m_Mesh.nNumVtx_U; nCnt--)
	{
		//判定用変数宣言
		float fJudge = (pVtx[nCnt - 1].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[nCnt - 1].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		if (nCnt == m_Mesh.nNumVtx_U - 1)
		{
			fJudge = (pVtx[0].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[0].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		}

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//縦の判定用の変数
	D3DXVECTOR3 *pPoint = NULL;

	//必要数のメモリを確保する
	if (pPoint == NULL)
	{
		pPoint = new D3DXVECTOR3[m_Mesh.nNumVtx_V];
	}

	//右の頂点を取得する
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V; nCnt++)
	{
		pPoint[nCnt] = pVtx[(m_Mesh.nNumVtx_U * (nCnt + 1)) - 1].pos;
	}

	//右の判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		//判定用変数宣言
		float fJudge = (pPoint[nCnt + 1].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[nCnt + 1].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			delete[] pPoint;
			return false;
		}
	}

	//左の頂点を取得する
	for (int nCnt = m_Mesh.nNumVtx_V - 1; nCnt >= 0; nCnt--)
	{
		pPoint[nCnt] = pVtx[m_Mesh.nNumVtx_U * nCnt].pos;
	}

	//左の判定
	for (int nCnt = m_Mesh.nNumVtx_V - 1; nCnt > 0; nCnt--)
	{
		//判定用変数宣言
		float fJudge = (pPoint[nCnt - 1].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[nCnt - 1].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			delete[] pPoint;
			return false;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return true;
}

//==========================================
//  メッシュフィールド上の存在判定(押し戻し)
//==========================================
bool CObject_Mesh::OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 *pVecLine, D3DXVECTOR3 *pVecToPos)
{
	//ローカル変数宣言
	int nCntPoint = 0;

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//上の存在判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		//判定用変数宣言
		float fJudge = (pVtx[nCnt + 1].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[nCnt + 1].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		*pVecLine = pVtx[nCnt + 1].pos - pVtx[nCnt].pos;
		*pVecToPos = pVtx[nCnt + 1].pos - oldpos;
		if (nCnt == m_Mesh.nNumVtx_U - 1)
		{
			fJudge = (pVtx[0].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[0].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
			*pVecLine = D3DXVECTOR3(pVtx[0].pos.x - pVtx[nCnt].pos.x, pVtx[0].pos.y - pVtx[nCnt].pos.y, pVtx[0].pos.z - pVtx[nCnt].pos.z);
		}

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//下の存在判定
	for (int nCnt = m_Mesh.nNumVtx - 1; nCnt > m_Mesh.nNumVtx - m_Mesh.nNumVtx_U; nCnt--)
	{
		//判定用変数宣言
		float fJudge = (pVtx[nCnt - 1].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[nCnt - 1].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
		*pVecLine = pVtx[nCnt - 1].pos - pVtx[nCnt].pos;
		*pVecToPos = pVtx[nCnt - 1].pos - oldpos;
		if (nCnt == m_Mesh.nNumVtx_U - 1)
		{
			fJudge = (pVtx[0].pos.z - pVtx[nCnt].pos.z) * (pos.x - pVtx[nCnt].pos.x) - (pVtx[0].pos.x - pVtx[nCnt].pos.x) * (pos.z - pVtx[nCnt].pos.z);
			*pVecLine = D3DXVECTOR3(pVtx[0].pos.x - pVtx[nCnt].pos.x, pVtx[0].pos.y - pVtx[nCnt].pos.y, pVtx[0].pos.z - pVtx[nCnt].pos.z);
		}

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//縦の判定用の変数
	D3DXVECTOR3 *pPoint = NULL;

	//必要数のメモリを確保する
	if (pPoint == NULL)
	{
		pPoint = new D3DXVECTOR3[m_Mesh.nNumVtx_V];
	}

	//右の頂点を取得する
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V; nCnt++)
	{
		pPoint[nCnt] = pVtx[(m_Mesh.nNumVtx_U * (nCnt + 1)) - 1].pos;
	}

	//右の判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		//判定用変数宣言
		float fJudge = (pPoint[nCnt + 1].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[nCnt + 1].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);
		*pVecLine = pPoint[nCnt + 1] - pPoint[nCnt];
		*pVecToPos = pPoint[nCnt + 1] - oldpos;

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			delete[] pPoint;
			return false;
		}
	}

	//左の頂点を取得する
	for (int nCnt = m_Mesh.nNumVtx_V - 1; nCnt >= 0; nCnt--)
	{
		pPoint[nCnt] = pVtx[m_Mesh.nNumVtx_U * nCnt].pos;
	}

	//左の判定
	for (int nCnt = m_Mesh.nNumVtx_V - 1; nCnt > 0; nCnt--)
	{
		//判定用変数宣言
		float fJudge = (pPoint[nCnt - 1].z - pPoint[nCnt].z) * (pos.x - pPoint[nCnt].x) - (pPoint[nCnt - 1].x - pPoint[nCnt].x) * (pos.z - pPoint[nCnt].z);
		*pVecLine = pPoint[nCnt - 1] - pPoint[nCnt];
		*pVecToPos = pPoint[nCnt - 1] - oldpos;

		//範囲外だった場合false
		if (fJudge < 0.0f)
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			delete[] pPoint;
			return false;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
	
	return true;
}