//==========================================
//
//  オブジェクトクラス(object.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "pause.h"
#include "camera.h"
#include "debugproc.h"
#include "effect.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CObject *CObject::m_apObject[PRIORITY_NUM][MAX_OBJECT] = {};
int CObject::m_nNumObject = 0;

//==========================================
//  コンストラクタ
//==========================================
CObject::CObject(int nPriority)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_apObject[nPriority][nCntObject] = this;
			m_nID = nCntObject;
			m_nNumObject++;
			break;
		}
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPriority = nPriority;
	m_type = TYPE_NONE;
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
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}

//==========================================
//  全オブジェクトの更新
//==========================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				if (CManager::GetPause()->GetState() == false || m_apObject[nCntPriority][nCntObject]->m_type == CObject::TYPE_TIMER)
				{
					m_apObject[nCntPriority][nCntObject]->Update();
				}
			}
		}
	}
}

//==========================================
//  全オブジェクトの描画
//==========================================
void CObject::DrawAll(void)
{
	//カメラの取得
	CCamera *pCamera = CManager::GetCamera();

	//カメラの設定
	pCamera->SetCamera();

	CManager::GetDebugProc()->Print("オブジェクト数 : %d\n", m_nNumObject);
	CManager::GetDebugProc()->Print("エフェクト数 : %d\n", CEffect::GetNum());

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//==========================================
//  単体の破棄
//==========================================
void CObject::Release(void)
{
	//優先順位を保存
	int nPriority = m_nPriority;

	//インデックスを保存
	int nIdx = m_nID;

	if (m_apObject[nPriority][nIdx] != NULL)
	{
		delete m_apObject[nPriority][nIdx];
		m_apObject[nPriority][nIdx] = NULL;
		m_nNumObject--;
	}
}
