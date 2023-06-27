//==========================================
//
//  バレットクラス(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  マクロ定義
//==========================================
#define BULLET_SPEED (20.0f) //弾速

//==========================================
//  コンストラクタ
//==========================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//==========================================
//  デストラクタ
//==========================================
CBullet::~CBullet()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBullet::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_BULLET);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBullet::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBullet::Update(void)
{
	//寿命を減らす
	m_nLife--;

	//寿命がなくなったら削除する
	if (m_nLife <= 0)
	{
		this->Release();
		return;
	}

	//移動量を加算する
	m_pos += m_move;

	//更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CBullet::Draw(void)
{
	//描画
	CObject3D::Draw();
}

//==========================================
//  生成処理
//==========================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife)
{
	//インスタンス生成
	CBullet *pBullet = NULL;

	//NULLチェック
	if (pBullet == NULL)
	{
		//メモリを確保
		pBullet = new CBullet;
	}

	if (pBullet == NULL)
	{
		return NULL;
	}

	//値を設定
	pBullet->m_pos = pos;
	pBullet->m_size = size;
	pBullet->m_move = move;
	pBullet->m_move.x = move.x * BULLET_SPEED;
	pBullet->m_move.z = move.z * BULLET_SPEED;
	pBullet->m_nLife = nLife;
	pBullet->m_rot.x = D3DX_PI * 0.5f;

	//初期化
	pBullet->Init();

	//テクスチャを割り当てる
	pBullet->BindTexture(CManager::GetTexture()->GetAddress(4));

	//ポインタを返す
	return pBullet;
}
