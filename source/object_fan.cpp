//==========================================
//
//  オブジェクトファンクラス(object_fan.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_fan.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CObject_Fan::CObject_Fan(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_pTexture = NULL;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fRadius = 0.0f;
	m_nNumPrimitive = 0;
}

//==========================================
//  デストラクタ
//==========================================
CObject_Fan::~CObject_Fan()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject_Fan::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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

	//頂点バッファの情報を設定
	SetVtx();

	//種類を設定
	SetType(TYPE_FIELD);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject_Fan::Uninit(void)
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
void CObject_Fan::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CObject_Fan::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxView; //計算用マトリックス

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

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

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nNumPrimitive);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//==========================================
//  当たり判定処理
//==========================================
bool CObject_Fan::OnMesh(const D3DXVECTOR3 pos)
{
	//ローカル変数宣言
	//int nCntPoint = 0;

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//判定
	for (int nCnt = 1; nCnt <= m_nNumPrimitive; nCnt++)
	{
		int IdxStart = nCnt; //左
		int IdxEnd = nCnt + 1; //右
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return true;
}

//==========================================
//  当たり判定処理
//==========================================
bool CObject_Fan::OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 * pVecLine, D3DXVECTOR3 * pVecToPos)
{
	return false;
}

//==========================================
//  ポリゴンの上にいる判定
//==========================================
bool CObject_Fan::CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const
{
	return (posEnd.z - posStart.z) * (posJudge.x - posStart.x) - (posEnd.x - posStart.x) * (posJudge.z - posStart.z) < 0.0f;
}

//==========================================
//  生成処理
//==========================================
CObject_Fan *CObject_Fan::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumPrimitive, float fRadius)
{
	//インスタンス生成
	CObject_Fan *pFan = NULL;

	//NULLチェック
	if (pFan == NULL)
	{
		//メモリを確保
		pFan = new CObject_Fan;
	}

	if (pFan == NULL)
	{
		return NULL;
	}

	//分割数を設定
	pFan->m_pos = pos;
	pFan->m_rot = rot;
	pFan->m_nNumPrimitive = nNumPrimitive;
	pFan->m_nNumVtx = pFan->m_nNumPrimitive + 2;
	pFan->m_fRadius = fRadius;

	//初期化
	pFan->Init();

	//テクスチャを割り当てる
	pFan->BindTexture(CManager::GetTexture()->GetAddress(CTexture::FIELD));

	//ポインタを返す
	return pFan;
}

//==========================================
//  頂点の設定
//==========================================
void CObject_Fan::SetVtx(void)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nNumPrimitive + 2; nCntVtx++)
	{
		//法線の設定
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntVtx].col = m_Color;

		//テクスチャ座標の設定
		pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //中心座標を設定

	//外周の頂点を設定
	for (int nCntVtx = 1; nCntVtx <= m_nNumPrimitive; nCntVtx++)
	{
		//角度を算出
		float fAngle = ((nCntVtx / (float)(m_nNumPrimitive)) * (360.0f)) - 180.0f;
		fAngle = D3DXToRadian(fAngle);

		//各頂点に座標を与える
		pVtx[nCntVtx].pos = D3DXVECTOR3
		(
			sinf(fAngle) * m_fRadius,
			0.0f,
			cosf(fAngle) * m_fRadius
		);
	}

	//最後の頂点を設定
	pVtx[m_nNumVtx - 1] = pVtx[1];

	//テクスチャ座標を設定
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		//座標を正規化する
		D3DXVECTOR2 texPos = D3DXVECTOR2(pVtx[nCnt].pos.x, pVtx[nCnt].pos.z);
		D3DXVec2Normalize(&pVtx[nCnt].tex, &texPos);
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
