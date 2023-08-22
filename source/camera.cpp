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
#define DISTANCE (1000.0f) //視点と注視点の距離
#define DISTANCE_LEVEL (0.4f) //xzの割合
#define SPEED (0.05f) //カメラのスピード
#define MAX_ROT (D3DX_PI * 0.99f) //視点の限界角
#define MIN_ROT (D3DX_PI * 0.01f) //視点の限界角
#define FOV_MIN (45.0f) //視野角の最低値
#define FOV_MAX (54.0f) //視野角の最大値

//==========================================
//  コンストラクタ
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 150.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FOV = FOV_MIN;
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

	//位置を設定
	CalcPos(SLIP_OFF);

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
	CalcPos(SLIP_ON);
	//ThirdPerson();

	//視野角の更新
	CalcFOV();

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
		D3DXToRadian(m_FOV),
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
	//マウス
	m_posR += CManager::GetMouse()->GetMouseMove();
	m_posV += CManager::GetMouse()->GetMouseMove();

	//キーボード
	if (CManager::GetKeyboard()->GetPress(DIK_Q))
	{
		m_rot.x -= 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		m_rot.x += 0.01f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_R))
	{
		m_rot.y += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_V))
	{
		m_rot.y -= 0.01f;
	}
}

//==========================================
//  カメラ位置計算処理
//==========================================
void CCamera::CalcPos(SLIP slipFlag)
{
	m_posR = CGameManager::GetPlayer()->GetPos();
	m_rot.x = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);
	m_rot.z = tanf(m_posR.y - m_posV.y);

	//移動量を取得
	D3DXVECTOR3 rot = CGameManager::GetPlayer()->GetRot();

	if (slipFlag == SLIP_ON)
	{
		float fRotMove, fRotDest, fRotDiff;

		//現在の角度と目的の角度の差分を計算
		fRotMove = m_rot.y;
		fRotDest = rot.y;
		fRotDiff = fRotDest - fRotMove;

		//角度の補正
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff -= D3DX_PI * 2.0f;
		}
		else if (fRotDiff <= -D3DX_PI)
		{
			fRotDiff += D3DX_PI * 2.0f;
		}

		//方向転換の慣性
		fRotMove += fRotDiff * 0.03f;

		//角度の補正
		if (fRotMove > D3DX_PI)
		{
			fRotMove -= D3DX_PI * 2.0f;
		}
		else if (fRotMove <= -D3DX_PI)
		{
			fRotMove += D3DX_PI * 2.0f;
		}

		//方向を適用する
		m_rot.y = fRotMove;
	}
	else
	{
		m_rot = rot;
	}

	//注視点のずれを設定
	D3DXVECTOR3 slip = D3DXVECTOR3(sinf(m_rot.y) * -100.0f, 0.0f, cosf(m_rot.y) * -100.0f);

	m_posR += slip;
	m_posV = D3DXVECTOR3(m_posR.x, DISTANCE, m_posR.z - DISTANCE * DISTANCE_LEVEL);
}

//==========================================
//  視野角の計算
//==========================================
void CCamera::CalcFOV(void)
{
	//ローカル変数宣言
	float fDeff = FOV_MIN;

	//場合分け
	switch (CGameManager::GetState())
	{
	case CGameManager::SHOT:
		fDeff = FOV_MIN;
		break;
	case CGameManager::BLADE:
		fDeff = FOV_MAX;
		break;
	}

	//目標の視野角まで拡縮する
	m_FOV += (fDeff - m_FOV) * 0.08f;
}
