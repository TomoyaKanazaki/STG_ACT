//==========================================
//
//  リザルトカメラクラス(camera_result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_result.h"
#include "manager.h"
#include "debugproc.h"
#include "object_fan.h"

//==========================================
//  コンストラクタ
//==========================================
CCameraResult::CCameraResult()
{
	m_fAngle = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CCameraResult::~CCameraResult()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCameraResult::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraResult::Update(void)
{
	FirstPerson();
}
