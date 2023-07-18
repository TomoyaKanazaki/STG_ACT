//==========================================
//
//  モーションクラス(moton.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "motion.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CMotion::INFO *CMotion::m_pInfo = NULL;
int CMotion::m_nNumMotion = 0;

//==========================================
//  コンストラクタ
//==========================================
CMotion::CMotion()
{
	m_ppModel = NULL;
	m_Chara = MOTION_NONE;
	m_Info.bLoop = false;
	m_Info.pKeyInfo = NULL;
	m_Info.nNumKey = 0;
	m_nNumModel = 0;
}

//==========================================
//  デストラクタ
//==========================================
CMotion::~CMotion()
{

}

//==========================================
//  更新処理
//==========================================
void CMotion::Update(void)
{

}

//==========================================
//  モデルの設定処理
//==========================================
void CMotion::SetModel(CModel **ppModel, int nNum, CHARA type)
{
	//モデルを記録
	m_ppModel = ppModel;

	//モデル数を記録
	m_nNumModel = nNum;

	//キャラクター情報を記録
	m_Chara = type;
}

//==========================================
//  モーションの設定処理
//==========================================
void CMotion::Set(int type)
{

}

//==========================================
//  読み込み処理
//==========================================
void CMotion::Load(void)
{

}

//==========================================
//  情報の破棄
//==========================================
void CMotion::UnLoad(void)
{
	//モーション情報の破棄
	if (m_pInfo != NULL)
	{
		delete[] m_pInfo;
		m_pInfo = NULL;
	}
}
