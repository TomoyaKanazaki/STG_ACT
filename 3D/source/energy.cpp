//==========================================
//
//  エネルギークラス(energy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "energy.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "gamemanager.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CEnergy::m_fMax = 650.0f;
const float CEnergy::m_fAdd = CEnergy::m_fMax * 0.05f;

//==========================================
//  コンストラクタ
//==========================================
CEnergy::CEnergy()
{
	m_fEnergy = 0.0f;
	m_fBaseHight = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CEnergy::~CEnergy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnergy::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_ENERGY);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnergy::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnergy::Update(void)
{
	//最大値の補正
	if (m_fEnergy > m_fMax)
	{
		m_fEnergy = m_fMax;
	}

	//ゲージの伸縮
	float fSizeMove = m_size.y, fSizeDest = m_fEnergy, fSizeDiff; //計算用変数
	fSizeDiff = fSizeDest - fSizeMove; //現在の大きさと目標の大きさの差分を求める
	m_size.y += fSizeDiff * 0.1f; //値を補正して加算する

	//更新情報の適用
	CObject2D::Update();

	//エネルギーを減らす
	if (CGameManager::GetState() == CGameManager::BLADE)
	{
		m_fEnergy--;
	}

#if _DEBUG
	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		m_fEnergy = m_fMax;
	}
#endif
}

//==========================================
//  描画処理
//==========================================
void CEnergy::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CEnergy *CEnergy::Create(const D3DXVECTOR3 pos, const float fWidth)
{
	//インスタンス生成
	CEnergy *pEnergy = NULL;

	//NULLチェック
	if (pEnergy == NULL)
	{
		//メモリを確保
		pEnergy = new CEnergy;
	}

	//値を割り当てる
	pEnergy->m_pos = pos;
	pEnergy->m_fBaseHight = pos.y;

	//初期値を生成する
	pEnergy->m_size.x = fWidth;
	pEnergy->m_size.y = pEnergy->m_fEnergy;

	//初期化
	if (pEnergy != NULL)
	{
		pEnergy->Init();
	}

	//ポインタを返す
	return pEnergy;
}

