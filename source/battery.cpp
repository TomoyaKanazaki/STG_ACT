//==========================================
//
//  バッテリークラス(battery.cpp)
//  Author ; Tomoya Kanazaki
//
//==========================================
#include "battery.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CBattery::mc_fMax = 1000.0f; //最大値
const float CBattery::mc_fTime = 120.0f; //制限時間
const float CBattery::mc_fSab = (CBattery::mc_fMax / (CBattery::mc_fTime * 60.0f)); //制限時間

//==========================================
//  コンストラクタ
//==========================================
CBattery::CBattery(int nPriority) : CObject2D(nPriority)
{
	m_fBattery = mc_fMax;
}

//==========================================
//  デストラクタ
//==========================================
CBattery::~CBattery()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBattery::Init(void)
{
	//各種値を設定
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 680.0f, 0.0f);
	m_size = D3DXVECTOR3(m_fBattery, 40.0f, 0.0f);

	//実体の初期化
	CObject2D::Init();

	//値を返す
	return S_OK;
}

//==========================================
//  終了処理
//=========================================
void CBattery::Uninit(void)
{
	//実体の終了
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBattery::Update(void)
{
	//常に減少し続けるバッテリー
	m_fBattery -= mc_fSab;

	//0を下回った場合補正
	if (m_fBattery <= 0)
	{
		m_fBattery = 0;
	}

	CManager::GetDebugProc()->Print("バッテリー最大値 : %f\n", mc_fMax);
	CManager::GetDebugProc()->Print("バッテリー減少量 : %f\n", mc_fSab);
	CManager::GetDebugProc()->Print("バッテリー現在値 : %f\n", m_fBattery);

	//現在の値をゲージの長さに反映
	m_size.x = m_fBattery;

	//実体の更新
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CBattery::Draw(void)
{
	//実体の描画
	CObject2D::Draw();
}

//==========================================
//  加算処理
//==========================================
void CBattery::Add(const float fAdd)
{
	//最大値未満の場合加算可能
	if (m_fBattery < mc_fMax)
	{
		//加算
		m_fBattery += fAdd;

		//最大値を超えた場合補正する
		if (m_fBattery > mc_fMax)
		{
			m_fBattery = mc_fMax;
		}
	}
}

//==========================================
//  減算処理
//==========================================
void CBattery::Sab(const float fSab)
{
	//0以上の場合減算可能
	if (0 < m_fBattery)
	{
		//減算
		m_fBattery -= fSab;

		//0を下回った場合補正
		if (m_fBattery <= 0)
		{
			m_fBattery = 0;
		}
	}
}

//==========================================
//  生成処理
//==========================================
CBattery *CBattery::Create()
{
	//インスタンス生成
	CBattery *pBattery = NULL;

	//メモリを確保
	pBattery = new CBattery;

	//初期化
	pBattery->Init();

	//ポインタを返す
	return pBattery;
}
