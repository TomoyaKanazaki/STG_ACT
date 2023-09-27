//==========================================
//
//  �����o���̓G(enemy_push.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_push.h"
#include "gamemanager.h"
#include "player.h"
#include "model.h"
#include "motion.h"
#include "effect.h"
#include "manager.h"
#include "debugproc.h"
#include "object_fan.h"
#include "sound.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CEnemy_Push::mc_fPush = 400.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Push::CEnemy_Push(int nPriority) : CEnemy(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Push::~CEnemy_Push()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Push::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_NORMAL_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PUSH_LAYER);

	//���f���p�̃������̊m��
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel*[m_pLayer->nNumModel];
	}

	//�K�v�ȃ��f���𐶐�
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//��ɂ���
		m_ppModel[nCnt] = NULL;

		//�e�����݂��Ȃ��ꍇ
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//���[�V�������̐���
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}

	CEnemy::Init();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Push::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Push::Update(void)
{
	//�p�x���X�V
	D3DXVECTOR3 rotModel = m_ppModel[1]->GetRot();
	rotModel.y += 0.1f;

	//�p�x�̕␳
	if (rotModel.y > D3DX_PI)
	{
		rotModel.y = -D3DX_PI;
	}
	if (rotModel.y < -D3DX_PI)
	{
		rotModel.y = D3DX_PI;
	}

	//�G�t�F�N�g���o��
	if (this->GetType() != CObject::TYPE_BULLET_ENEMY)
	{
		D3DXVECTOR3 posEffect = D3DXVECTOR3(m_pos.x + (sinf(rotModel.y) * mc_fPush), 30.0f, m_pos.z + (cosf(rotModel.y) * mc_fPush));
		CEffect::Create(posEffect, m_size * 0.5f, D3DXCOLOR(0.2f, 0.7f, 0.8f, 1.0f), 100);
	}

	//�p�x��K�p
	m_ppModel[1]->SetRot(rotModel);

	//�����痎����
	if (!CGameManager::GetFan()->OnMesh(m_pos))
	{
		m_move.y -= 1.0f;
	}

	Target();
	Push();
	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Push::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �e������
//==========================================
void CEnemy_Push::Push(void)
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�܂ł̋����𔻒�
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;
	vecToPlayer.y = 0.0f;
	float fLength = (vecToPlayer.x * vecToPlayer.x) + (vecToPlayer.z * vecToPlayer.z);

	//�ڐG����
	if (mc_fPush * mc_fPush >= fLength)
	{
		CManager::GetSound()->Play(CSound::SOUND_LABEL_PUSH);

		CGameManager::GetPlayer()->SetMove(vecToPlayer * 0.5f);
	}
}

//==========================================
//  �v���C���[������
//==========================================
void CEnemy_Push::Target(void)
{
	//�v���C���[�̍��p���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�Ɍ������x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;

	//�v���C���[�̕���������
	float fRot = atan2f(-vecToPlayer.x, -vecToPlayer.z);
	m_rot.y = fRot;
}
