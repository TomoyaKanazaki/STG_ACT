//==========================================
//
//  xオブジェクトクラス(object_x.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_x.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CObject_X::CObject_X(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_mtxWorld = {};
}

//==========================================
//  デストラクタ
//==========================================
CObject_X::~CObject_X()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject_X::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//情報の保存
	m_pos = pos;
	m_size = size;
	m_rot = rot;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		"data\\MODEL\\Player\\player.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh
	);

	//マテリアル数分のポインタを確保する
	if (m_pTexture == NULL)
	{
		m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];
	}
	else
	{
		return E_FAIL;
	}

	//マテリアルデータへのポインタを取得
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャを保存し、管理番号を取得する
			int nNumTexID = CManager::GetTexture()->Regist(pMat[nCntMat].pTextureFilename);

			//テクスチャを割り当てる
			m_pTexture[nCntMat] = CManager::GetTexture()->GetAddress(nNumTexID);

			D3DXCreateTextureFromFile
			(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]
			);
		}
		else
		{
			m_pTexture[nCntMat] = NULL;
		}
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject_X::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_dwNumMat; nCnt++)
		{
			if (m_pTexture[nCnt] != NULL)
			{
				m_pTexture[nCnt]->Release();
				m_pTexture[nCnt] = NULL;
			}
		}
		delete[] m_pTexture;
		m_pTexture = NULL;
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CObject_X::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CObject_X::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアルの保存用
	D3DXMATERIAL *pMat; //マテリアルへのポインタ

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

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデルの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存しているマテリアルを復元
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  生成処理
//==========================================
CObject_X * CObject_X::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CObject_X *pObject_X = NULL;

	//NULLチェック
	if (pObject_X == NULL)
	{
		//メモリを確保
		pObject_X = new CObject_X;
	}

	//初期化
	if (pObject_X != NULL)
	{
		pObject_X->Init(pos, size, rot);
	}

	//ポインタを返す
	return pObject_X;
}
