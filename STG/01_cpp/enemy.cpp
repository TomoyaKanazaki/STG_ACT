//==========================================
//
//  エネミークラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "object.h"

//==========================================
//  マクロ定義
//==========================================
#define ENEMY_SPEED (5.0f) //エネミーの移動速度

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
int CEnemy::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy()
{
	m_move = D3DXVECTOR3((float)(rand() % 100), (float)(rand() % 100), 0.0f);
	if (rand() % 2)
	{
		m_move.x *= -1.0f;
	}
	if (rand() % 2)
	{
		m_move.y *= -1.0f;
	}

	m_nSpeed = ENEMY_SPEED;
	m_fRotMove = 0.0f;
	m_fRotDest = 0.0f;
	m_fRotDiff = 0.0f;

	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_ENEMY);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();

	m_nNum--;
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	//移動処理
	Move();
	
	//回転処理
	Rotate();

	//更新する
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  テクスチャの読み込み
//==========================================
HRESULT CEnemy::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/Enemy_0.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  テクスチャの破棄
//==========================================
void CEnemy::UnLoad(void)
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
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CEnemy *pEnemy = NULL;

	//NULLチェック
	if (pEnemy == NULL)
	{
		//メモリを確保
		pEnemy = new CEnemy;
	}

	//初期化
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, size, rot);
	}

	//テクスチャを割り当てる
	pEnemy->BindTexture(m_pTexture);

	//ポインタを返す
	return pEnemy;
}

//==========================================
//  移動処理
//==========================================
void CEnemy::Move(void)
{
	//x方向の移動制限
	if (m_pos.x + (m_size.x * 0.5f) > SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - (m_size.x * 0.5f);
		m_move.x *= -1.0f;
	}
	if (m_pos.x - (m_size.x * 0.5f) < 0.0f)
	{
		m_pos.x = (m_size.x * 0.5f);
		m_move.x *= -1.0f;
	}

	//y方向の移動制限
	if (m_pos.y + (m_size.y * 0.5f) > SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - (m_size.y * 0.5f);
		m_move.y *= -1.0f;
	}
	if (m_pos.y - (m_size.y * 0.5f) < 0.0f)
	{
		m_pos.y = (m_size.y * 0.5f);
		m_move.y *= -1.0f;
	}

	//正規化
	D3DXVec3Normalize(&m_move, &m_move);
	m_move.x *= m_nSpeed;
	m_move.y *= m_nSpeed;

	//敵同士の当たり判定
	Collision();

	//移動処理
	m_pos += m_move;
}

//==========================================
//  回転処理
//==========================================
void CEnemy::Rotate(void)
{
	//現在角度の取得
	m_fRotMove = m_rot.z;
	m_fRotDest = m_rot.z + 0.2f;

	//目標-現在角度の差分を取得
	m_fRotDiff = m_fRotDest - m_fRotMove;

	//差分の値を補正
	if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
	{
		if (m_fRotDiff > D3DX_PI)
		{
			m_fRotDiff += (-D3DX_PI * 2);
		}
		else if (m_fRotDiff <= -D3DX_PI)
		{
			m_fRotDiff += (D3DX_PI * 2);
		}
	}

	//回転する
	m_rot.z += m_fRotDiff * 0.2f;

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
}

//==========================================
//  敵同士の当たり判定
//==========================================
void CEnemy::Collision(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (nCntObj != GetID())
		{
			//インスタンス生成
			CObject *pObj;

			//オブジェクトを取得
			pObj = GetObject(nCntObj);

			//NULLチェック
			if (pObj != NULL)
			{
				//種類の取得
				TYPE type = pObj->GetType();

				if (type == TYPE_ENEMY) //敵の場合
				{
					//敵の各情報を取得する
					D3DXVECTOR3 pos = pObj->GetPos();
					D3DXVECTOR3 size = pObj->GetSize();

					//敵と弾の距離を取得
					float fLength = (pos.x - m_pos.x) * (pos.x - m_pos.x) + (pos.y - m_pos.y) * (pos.y - m_pos.y);

					//判定距離を取得
					float fOutLine = (size.x - m_size.x * 0.3f) * (size.x - m_size.x * 0.3f) + (size.y - m_size.y * 0.3f) * (size.y - m_size.y * 0.3f);

					if (fLength < fOutLine)
					{
						m_move.x *= -1.0f;
						m_move.y *= -1.0f;
					}
				}
			}
		}
	}
}