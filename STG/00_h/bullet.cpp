//==========================================
//
//  弾クラス(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "object2D_anim.h"
#include "debugproc.h"

//==========================================
//  マクロ定義
//==========================================
#define BULLET_SPEED (5.0f) //弾の速度
#define BULLET_LIFE (120) //弾の寿命

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
int CBullet::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CBullet::CBullet()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = BULLET_SPEED;
	m_nLife = BULLET_LIFE;
	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CBullet::~CBullet()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	m_move.x = -sinf(m_rot.z) * BULLET_SPEED;
	m_move.y = -cosf(m_rot.z) * BULLET_SPEED;

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBullet::Update(void)
{
	//寿命を減らす
	m_nLife--;

	//移動
	m_pos += m_move;

	//回転
	m_rot.z += 0.3f;

	//回転角度の補正
	if (m_rot.z > D3DX_PI || m_rot.z < -D3DX_PI)
	{
		if (m_rot.z > D3DX_PI)
		{
			m_rot.z += (-D3DX_PI * 2);
		}
		else if (m_rot.z < -D3DX_PI)
		{
			m_rot.z += (D3DX_PI * 2);
		}
	}

	//更新する
	CObject2D::Update();

	//移動制限
	if (
		m_pos.x - (m_size.x * 0.5f) > SCREEN_WIDTH ||
		m_pos.x + (m_size.x * 0.5f) < 0.0f ||
		m_pos.y - (m_size.y * 0.5f) > SCREEN_HEIGHT ||
		m_pos.y + (m_size.y * 0.5f) < 0.0f
		)
	{
		this->Release();
	}
	else if (m_nLife <= 0)
	{
		this->Release();
		CObject2D_Anim::Create(m_pos, D3DXVECTOR3(m_size.x * 1.5f, m_size.y * 1.5f, 0.0f), 8, m_rot);
	}
}

//==========================================
//  描画処理
//==========================================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  テクスチャの読み込み
//==========================================
HRESULT CBullet::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/explosion.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  テクスチャの破棄
//==========================================
void CBullet::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==========================================
//  オブジェクト生成処理
//==========================================
CBullet *CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CBullet *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{
		//メモリを確保
		pPlayer = new CBullet;
	}

	//初期化
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, size, rot);
	}

	//テクスチャを割り当てる
	pPlayer->BindTexture(m_pTexture);

	//ポインタを返す
	return pPlayer;
}
