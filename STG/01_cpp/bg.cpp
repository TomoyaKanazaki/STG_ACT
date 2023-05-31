//==========================================
//
//  背景クラス(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"

//==========================================
//  コンストラクタ
//==========================================
CBg::CBg()
{

}


CBg::~CBg()
{
}

HRESULT CBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	return S_OK;
}

void CBg::Uninit(void)
{
}

void CBg::Update(void)
{
}

void CBg::Draw(void)
{
}

CBg CBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	return CBg();
}
