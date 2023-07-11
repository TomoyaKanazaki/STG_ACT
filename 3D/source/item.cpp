//==========================================
//
//  アイテムクラス(item.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "gamemanager.h"

//==========================================
//  マクロ定義
//==========================================
#define GET_SPEED (10.0f) //プレイヤーに近づく速度

//==========================================
//  コンストラクタ
//==========================================
CItem::CItem(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = ITEMS_MAX;
}

//==========================================
//  デストラクタ
//==========================================
CItem::~CItem()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CItem::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//ビルボードに設定する
	SwitchBillboard();

	//タイプの設定
	SetType(TYPE_ITEM);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CItem::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CItem::Update(void)
{
	//プレイヤーの位置を取得
	D3DXVECTOR3 TargetPos = CGameManager::GetPlayer()->GetPos();

	//移動先へのベクトルを算出
	D3DXVECTOR3 vecMove = TargetPos - m_pos;

	//プレイヤーとの距離を算出
	D3DXVECTOR2 vec2 = D3DXVECTOR2(vecMove.x, vecMove.z);
	if (D3DXVec2Length(&vec2) < 5.0f)
	{
		//近づいたら消す
		Uninit();
		return;
	}

	//値を補正
	D3DXVec3Normalize(&vecMove, &vecMove);
	m_move = vecMove * GET_SPEED;
	m_move.y = 0.0f;

	//移動
	m_pos += m_move;

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CItem::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CObject3D::Draw();

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CItem *CItem::Create(D3DXVECTOR3 pos, ITEMS type)
{
	//インスタンス生成
	CItem *pItem = NULL;

	//NULLチェック
	if (pItem == NULL)
	{
		//メモリを確保
		pItem = new CItem;
	}

	if (pItem == NULL)
	{
		return NULL;
	}

	//初期化
	pItem->Init();

	//種類を設定
	pItem->m_pos = pos;
	pItem->m_pos.y += 5.0f;
	pItem->m_type = type;
	pItem->m_size = D3DXVECTOR3(10.0f, 0.0f, 10.0f);

	//ポインタを返す
	return pItem;
}
