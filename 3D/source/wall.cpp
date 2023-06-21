//==========================================
//
//  床クラス(field.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CWall::CWall(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CWall::~CWall()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CWall::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//タイプの設定
	SetType(TYPE_WALL);

	if (FAILED(CObject3D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CWall::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CWall::Update(void)
{
	//更新する
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CWall::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	CObject3D::Draw();

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//==========================================
//  オブジェクト生成処理
//==========================================
CWall *CWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CWall *pField = NULL;

	//NULLチェック
	if (pField == NULL)
	{
		//メモリを確保
		pField = new CWall;
	}

	//初期化
	if (pField != NULL)
	{
		pField->Init(pos, size, rot);
	}

	//テクスチャを割り当てる
	//pField->BindTexture(CManager::GetTexture()->GetAddress(0));

	//ポインタを返す
	return pField;
}
