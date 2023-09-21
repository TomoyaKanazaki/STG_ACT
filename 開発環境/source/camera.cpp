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
#include "gamemanager.h"

//==========================================
//  コンストラクタ
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, HEIGHT, CAMERA_DISTANCE);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_diff = D3DXVECTOR3(0.0f, HEIGHT, CAMERA_DISTANCE);
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
	//注視点を設定
	m_posR = CGameManager::GetPlayer()->GetPos();

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
	//Rotate();
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
		20000.0f
	);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスを計算
	CreateViewMatrix();

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==========================================
//  ビューマトリックスの生成
//==========================================
D3DXMATRIX CCamera::CreateViewMatrix(void)
{
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

	return m_mtxView;
}
