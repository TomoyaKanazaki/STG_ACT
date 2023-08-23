//==========================================
//
//  床クラス(field.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CField::CField(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CField::~CField()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CField::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//タイプの設定
	SetType(TYPE_FIELD);

	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CField::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CField::Update(void)
{
	//更新する
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CField::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CObject3D::Draw();

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//==========================================
//  オブジェクト生成処理
//==========================================
CField *CField::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CField *pField = NULL;

	//NULLチェック
	if (pField == NULL)
	{
		//メモリを確保
		pField = new CField;
	}

	//初期化
	if (pField != NULL)
	{
		pField->Init(pos, size, rot);
	}

	//ポインタを返す
	return pField;
}
