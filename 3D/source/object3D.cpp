//==========================================
//
//  オブジェクト3Dクラス(object3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object3D.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bBillboard = false;
}

//==========================================
//  デストラクタ
//==========================================
CObject3D::~CObject3D()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//値を保存する
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	//ローカル変数宣言
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.z * m_size.z) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.z);

	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	)))
	{
		return E_FAIL;
	}

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (GetType() == TYPE_FIELD)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//頂点カラーの設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject3D::Uninit(void)
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
void CObject3D::Update(void)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (GetType() == TYPE_FIELD)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, 0.0f, m_fLength);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, 0.0f, m_fLength);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, 0.0f, -m_fLength);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, 0.0f, -m_fLength);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//頂点カラーの設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  描画処理
//==========================================
void CObject3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxView; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビルボードを作る
	if (m_bBillboard)
	{
		//ビューマトリックスの取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

		//値の補正
		m_mtxWorld._41 = m_pos.x;
		m_mtxWorld._42 = m_pos.y;
		m_mtxWorld._43 = m_pos.z;
	}
	else
	{
		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==========================================
//  テクスチャ座標の変更
//==========================================
void CObject3D::SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(min.x, min.y);
	pVtx[1].tex = D3DXVECTOR2(max.x, min.y);
	pVtx[2].tex = D3DXVECTOR2(min.x, max.y);
	pVtx[3].tex = D3DXVECTOR2(max.x, max.y);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  色の設定
//==========================================
void CObject3D::SetCol(const D3DXCOLOR col)
{
	//色を設定する
	m_col = col;

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//設定した色の適用
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
