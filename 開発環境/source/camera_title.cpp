//==========================================
//
//  タイトルカメラクラス(camera_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_title.h"

//==========================================
//  コンストラクタ
//==========================================
CCameraTitle::CCameraTitle()
{
	m_fAngle = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CCameraTitle::~CCameraTitle()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCameraTitle::Init(void)
{
	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraTitle::Update(void)
{
	//角度を更新
	m_fAngle += 0.01f;


	//角度の補正
	if (m_fAngle > D3DX_PI)
	{
		m_fAngle = -D3DX_PI;
	}
	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle = D3DX_PI;
	}

}
