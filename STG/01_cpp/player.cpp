//==========================================
//
//  プレイヤークラス(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "bullet.h"
#include "effect.h"

//==========================================
//  マクロ定義
//==========================================
#define MOUSE_SPEED (0.03f) //プレイヤーの移動速度(マウス)
#define KEYBOARD_SPEED (1.0f) //プレイヤーの移動速度(キーボード)

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSpeed = 0.0f;
	m_fRotMove = 0.0f;
	m_fRotDest = 0.0f;
	m_fRotDiff = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CPlayer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	if (FAILED(CObject2D::Init(pos, size, rot)))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_PLAYER);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	//移動処理
	Move();

	//回転処理
	Rotate();

	if (CManager::GetMouse()->GetTrigger(CMouse::BUTTON_LEFT) || CManager::GetKeyboard()->GetPress(DIK_SPACE))
	{
		CBullet::Create(m_pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), m_rot);
	}

	//更新する
	CObject2D::Update();

	//エフェクトを呼び出す
	CEffect::Create(m_pos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), m_rot, D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f),  30);
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  テクスチャの読み込み
//==========================================
HRESULT CPlayer::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "02_data/TEXTURE/Player.png", &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  テクスチャの破棄
//==========================================
void CPlayer::UnLoad(void)
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
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CPlayer *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{
		//メモリを確保
		pPlayer = new CPlayer;
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

//==========================================
//  移動処理
//==========================================
void CPlayer::Move(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 move = CManager::GetKeyboard()->GetWASD();
	D3DXVECTOR3 mouse = CManager::GetMouse()->GetMouseMove();

	//移動量の取得
	if (move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_move.x += mouse.x * MOUSE_SPEED;
		m_move.y += mouse.y * MOUSE_SPEED;
	}
	else
	{
		m_move.x += move.x * KEYBOARD_SPEED;
		m_move.y += move.y * KEYBOARD_SPEED;
	}
	m_pos += m_move;

	//x方向の移動制限
	if (m_pos.x + (m_size.x * 0.5f) > SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - (m_size.x * 0.5f);
	}
	if (m_pos.x - (m_size.x * 0.5f) < 0.0f)
	{
		m_pos.x = (m_size.x * 0.5f);
	}

	//y方向の移動制限
	if (m_pos.y + (m_size.y * 0.5f) > SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - (m_size.y * 0.5f);
	}
	if (m_pos.y - (m_size.y * 0.5f) < 0.0f)
	{
		m_pos.y = (m_size.y * 0.5f);
	}

	//慣性よる移動の停止
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
}

//==========================================
//  回転処理
//==========================================
void CPlayer::Rotate(void)
{
	//目標角度の取得
	if (m_move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		m_fRotDest = -atan2f(m_move.x, -m_move.y);
	}

	//現在角度の取得
	m_fRotMove = m_rot.z;

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
