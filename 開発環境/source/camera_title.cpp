//==========================================
//
//  タイトルカメラクラス(camera_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_title.h"
#include "manager.h"
#include "debugproc.h"
#include "object_fan.h"

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
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraTitle::Update(void)
{
	FirstPerson();
}
