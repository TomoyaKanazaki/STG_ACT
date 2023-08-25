//==========================================
//
//  カメラクラス(camera.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "target.h"
#include "gamemanager.h"

//==========================================
//  マクロ定義
//==========================================
#define DISTANCE (-300.0f) //視点と注視点の距離
#define HEIGHT (300.0f) //視点と注視点の距離
#define MAX_ROT (D3DX_PI * 0.99f) //視点の限界角
#define MIN_ROT (D3DX_PI * 0.01f) //視点の限界角

//==========================================
//  コンストラクタ
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_diff = D3DXVECTOR3(0.0f, HEIGHT, DISTANCE);
}

//==========================================
//  デストラクタ
//==========================================
CCamera::~CCamera()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCamera::Init(void)
{
	//上方向ベクトルを設定
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//ターゲットを生成
	CTarget::Create(D3DXVECTOR3(30.0f, 0.0f, 30.0f));

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CCamera::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CCamera::Update(void)
{
	//位置の更新
	//ThirdPerson();
	Move();

	CManager::GetDebugProc()->Print("注視点 : ( %f, %f, %f )\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetDebugProc()->Print("視点 : ( %f, %f, %f )\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetDebugProc()->Print("角度 : ( %f, %f, %f )\n", m_rot.x, m_rot.y, m_rot.z);
}

//==========================================
//  設定処理
//==========================================
void CCamera::SetCamera(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(54.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f
	);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH
	(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==========================================
//  一人称視点の操作
//==========================================
void CCamera::FirstPerson(void)
{
	//視点の値を更新
	m_rot += CManager::GetMouse()->GetMouseMove();

	//角度の補正
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//角度を更新
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.x)) * DISTANCE;
	m_posR.y = m_posV.y - cosf(m_rot.z) * DISTANCE;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * DISTANCE;
}

//==========================================
//  三人称視点の操作
//==========================================
void CCamera::ThirdPerson(void)
{
	//視点の値を更新
	m_rot += CManager::GetMouse()->GetMouseMove();

	//角度の補正
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//角度を更新
	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.x)) * DISTANCE;
	m_posV.y = m_posR.y + cosf(m_rot.z) * DISTANCE;
	m_posV.z = m_posR.z + (sinf(m_rot.z) * sinf(m_rot.x)) * DISTANCE;
}

//==========================================
//  移動
//==========================================
void CCamera::Move(void)
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//プレイヤーにカメラを追従させる
	m_posV = pos;
	m_posR = pos;

	//カメラの移動
	if (CManager::GetKeyboard()->GetPress(DIK_Z))
	{
		m_diff.x -= 3.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_C))
	{
		m_diff.x += 3.0f;
	}

	//プレイヤーからカメラを離す
	m_posV += m_diff;
	m_posR -= m_diff;
	m_posR.y = pos.y;
}
