//==========================================
//
//  背景のクラス(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "model.h"

//==========================================
//  コンストラクタ
//==========================================
CBg::CBg(int nPriority) : CObject(nPriority)
{
	m_ppModel = NULL;
	m_pLayer = NULL;
}

//==========================================
//  デストラクタ
//==========================================
CBg::~CBg()
{

}

//==========================================
//  初期化
//==========================================
HRESULT CBg::Init(void)
{
	//タイプの設定
	SetType(CObject::TYPE_BG);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::BG_LAYER);

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

	return S_OK;
}

//==========================================
//  終了
//==========================================
void CBg::Uninit(void)
{
	//モデルのポインタを破棄
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	Release();
}

//==========================================
//  更新
//==========================================
void CBg::Update(void)
{
	//角度を更新
	m_rot.x += 0.0001f;
	m_rot.y += 0.0002f;
	m_rot.z += 0.0003f;

	//角度の補正
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z = -D3DX_PI;
	}
	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z = D3DX_PI;
	}

	m_ppModel[0]->SetRot(m_rot);
}

//==========================================
//  描画
//==========================================
void CBg::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CBg *CBg::Create(void)
{
	//インスタンス生成
	CBg *pBg = NULL;

	//NULLチェック
	if (pBg == NULL)
	{
		//メモリを確保
		pBg = new CBg;
	}

	//初期化
	if (pBg != NULL)
	{
		pBg->Init();
	}

	//ポインタを返す
	return pBg;
}
