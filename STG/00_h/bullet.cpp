//==========================================
//
//  弾クラス(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "explosion.h"

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
	m_nSpeed = BULLET_SPEED;
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

	//タイプの設定
	SetType(TYPE_BULLET);

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

	//死亡条件
	if (CollisionEnemy())
	{
		return;
	}
	else if (
		m_pos.x - (m_size.x * 0.5f) > SCREEN_WIDTH ||
		m_pos.x + (m_size.x * 0.5f) < 0.0f ||
		m_pos.y - (m_size.y * 0.5f) > SCREEN_HEIGHT ||
		m_pos.y + (m_size.y * 0.5f) < 0.0f
		)
	{
		this->Release();
		return;
	}
	else if (m_nLife <= 0)
	{
		CExplosion::Create(m_pos, m_size, m_rot);
		this->Release();
		return;
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
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/bullet.png", &m_pTexture)))
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
	CBullet *pBullet = NULL;

	//NULLチェック
	if (pBullet == NULL)
	{
		//メモリを確保
		pBullet = new CBullet;
	}

	//初期化
	if (pBullet != NULL)
	{
		pBullet->Init(pos, size, rot);
	}

	//テクスチャを割り当てる
	pBullet->BindTexture(m_pTexture);

	//ポインタを返す
	return pBullet;
}

//==========================================
//  敵との当たり判定
//==========================================
bool CBullet::CollisionEnemy(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		//オブジェクトを取得
		CObject *pObj = GetObject(nCntObj);

		//NULLチェック
		if (pObj == NULL)
		{
			continue;
		}

		if (pObj->GetType() != TYPE_ENEMY) //敵の場合
		{
			continue;
		}

		//敵の各情報を取得する
		D3DXVECTOR3 pos = pObj->GetPos();
		D3DXVECTOR3 size = pObj->GetSize();

		//敵と弾の距離を取得
		float fLength = (pos.x - m_pos.x) * (pos.x - m_pos.x) + (pos.y - m_pos.y) * (pos.y - m_pos.y);

		//判定距離を取得
		float fOutLine = (size.x - m_size.x * 0.3f) * (size.x - m_size.x * 0.3f) + (size.y - m_size.y * 0.3f) * (size.y - m_size.y * 0.3f);

		if (fLength < fOutLine)
		{
			CExplosion::Create(m_pos, m_size, m_rot);
			pObj->Uninit();
			this->Release();
			return true;
		}
	}

	//当たっていない
	return false;
}
