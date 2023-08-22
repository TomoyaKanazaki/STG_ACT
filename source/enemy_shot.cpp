//==========================================
//
//  �e�����G�̃N���X(enemy_shot.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_shot.h"
#include "gamemanager.h"
#include "player.h"
#include "bullet.h"
#include "manager.h"
#include "input.h"

//==========================================
//  �}�N����`
//==========================================
#define SPEED (3.0f) //�e�̑��x

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyShot::CEnemyShot()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyShot::~CEnemyShot()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyShot::Init(void)
{
	CEnemy::Init();
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemyShot::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyShot::Update(void)
{
	Shot();
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyShot::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �e��������
//==========================================
void CEnemyShot::Shot(void)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//��������v���C���[�Ɍ������x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//�Z�o�����x�N�g������p�x���Z�o
	float rotVector = atan2f(vecToPlayer.x, vecToPlayer.z);

	//�Z�o�����p�x�������̕����ɂ���
	m_rot.y = rotVector;

	//�Z�o�����x�N�g���𐳋K������
	vecToPlayer.y = 0.0f;
	D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

	//�v���C���[�ւ̃x�N�g���ɔ{���^����
	vecToPlayer *= SPEED;

	//������^����
	D3DXVECTOR3 pos = m_pos;
	pos.y += 10.0f;

	//�e������
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CBullet::Create(pos, D3DXVECTOR3(25.0f, 25.0f, 0.0f), vecToPlayer, CBullet::ENEMY, CBullet::NORMAL_BULLET);
	}
}
