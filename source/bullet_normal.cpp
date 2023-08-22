//==========================================
//
//  ���i����e�̃N���X(bullet_normal.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet_normal.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CBulletNormal::CBulletNormal()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBulletNormal::~CBulletNormal()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBulletNormal::Init(void)
{
	CBullet::Init();
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBulletNormal::Uninit(void)
{
	CBullet::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBulletNormal::Update(void)
{
	CBullet::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBulletNormal::Draw(void)
{
	//CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	CBullet::Draw();
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}
