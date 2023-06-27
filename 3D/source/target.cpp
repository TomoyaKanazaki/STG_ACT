//==========================================
//
//  ターゲットクラス(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "texture.h"

CTarget::CTarget()
{
}

CTarget::~CTarget()
{
}

HRESULT CTarget::Init(void)
{
	return E_NOTIMPL;
}

void CTarget::Uninit(void)
{
}

void CTarget::Update(void)
{
}

void CTarget::Draw(void)
{
}

CTarget * CTarget::Create(const D3DXVECTOR3 size)
{
	//インスタンス生成
	CTarget *pTarget = NULL;

	//NULLチェック
	if (pTarget == NULL)
	{
		//メモリを確保
		pTarget = new CTarget;
	}

	if (pTarget == NULL)
	{
		return NULL;
	}

	//初期化
	pTarget->Init();

	//テクスチャを割り当てる
	pTarget->BindTexture(CManager::GetTexture()->GetAddress(1));

	//ポインタを返す
	return pTarget;
}
