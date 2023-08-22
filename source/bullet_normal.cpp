//==========================================
//
//  直進する弾のクラス(bullet_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet_normal.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CBulletNormal::CBulletNormal()
{

}

//==========================================
//  デストラクタ
//==========================================
CBulletNormal::~CBulletNormal()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBulletNormal::Init(void)
{
	CBullet::Init();
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CBulletNormal::Uninit(void)
{
	CBullet::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBulletNormal::Update(void)
{
	CBullet::Update();
}

//==========================================
//  描画処理
//==========================================
void CBulletNormal::Draw(void)
{
	//CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	CBullet::Draw();
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}
