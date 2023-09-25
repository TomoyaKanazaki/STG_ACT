//==========================================
//
//  スペースデブリ(debris.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "debris.h"
#include "model.h"
#include "motion.h"

//==========================================
//  コンストラクタ
//==========================================
CDebris::CDebris(int nPriority) : CEnemy(nPriority)
{
	m_Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  デストラクタ
//==========================================
CDebris::~CDebris()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CDebris::Init(void)
{
	//回転量を設定
	m_Rotate = D3DXVECTOR3
	(
		(float)(rand() % 628 - 314),
		(float)(rand() % 628 - 314),
		(float)(rand() % 628 - 314)
	);
	D3DXVec3Normalize(&m_Rotate, &m_Rotate);

	//角度を設定
	m_rot = D3DXVECTOR3
	(
		(float)(rand() % 628 - 314) * 0.01f,
		(float)(rand() % 628 - 314) * 0.01f,
		(float)(rand() % 628 - 314) * 0.01f
	);

	//位置を設定
	m_pos = D3DXVECTOR3
	(
		(float)(rand() % 6000 - 3000),
		(float)(rand() % 6000 - 3000),
		(float)(rand() % 6000 - 3000)
	);

	//タイプの設定
	SetType(CObject::TYPE_DEBRIS);

	//階層構造情報を生成
	int nLayer = rand() % 3 + 1;
	m_pLayer = CLayer::Set((CLayer::LAYERS)nLayer);

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

	//モーション情報の生成
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}

	return CEnemy::Init();
}

//==========================================
//  終了処理
//==========================================
void CDebris::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CDebris::Update(void)
{
	//回転
	m_rot += m_Rotate * 0.005f;

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

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CDebris::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  生成処理
//==========================================
CDebris * CDebris::Create()
{
	//インスタンス生成
	CDebris *pDebris = NULL;

	//NULLチェック
	if (pDebris == NULL)
	{
		//メモリを確保
		pDebris = new CDebris;
	}

	//初期化
	if (pDebris != NULL)
	{
		pDebris->Init();
	}

	//ポインタを返す
	return pDebris;
}
