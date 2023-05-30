//==========================================
//
//  オブジェクトクラス(object.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object.h"
#include "renderer.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CObject *CObject::m_apObject[MAX_OBJECT] = {};
int CObject::m_nNumObject = 0;

//==========================================
//  コンストラクタ
//==========================================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;
			m_nID = nCntObject;
			m_nNumObject++;
			break;
		}
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  デストラクタ
//==========================================
CObject::~CObject()
{

}

//==========================================
//  全オブジェクトの破棄
//==========================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//==========================================
//  全オブジェクトの更新
//==========================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Update();
		}
	}
}

//==========================================
//  全オブジェクトの描画
//==========================================
void CObject::DrawAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}

//==========================================
//  単体の破棄
//==========================================
void CObject::Release(void)
{
	//インデックスを保存
	int nIdx = m_nID;

	if (m_apObject[nIdx] != NULL)
	{
		delete m_apObject[nIdx];
		m_apObject[nIdx] = NULL;
		m_nNumObject--;
	}
}
