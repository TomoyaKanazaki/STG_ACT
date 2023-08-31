//==========================================
//
//  �{�X�N���X(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "debugproc.h"
#include "model.h"
#include "renderer.h"
#include "particle.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss::CBoss()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBoss::~CBoss()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBoss::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS_LAYER);

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

	CEnemy::Init();

	//�G�l�~�[�^�O���㏑��
	SetType(CObject::TYPE_BOSS);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CBoss::Uninit(void)
{
	//�p�[�e�B�N���𔭐�
	D3DXVECTOR3 color = D3DXVECTOR3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	CParticle::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(color.x, color.y, color.z, 1.0f), 50, 50, 50, 50);
	CParticle::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(color.z, color.x, color.y, 1.0f), 50, 50, 50, 50);
	CParticle::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXCOLOR(color.y, color.z, color.x, 1.0f), 50, 50, 50, 50);

	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBoss::Update(void)
{
	//��]
	Rotate();

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBoss::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CEnemy::Draw();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��]����
//==========================================
void CBoss::Rotate()
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�Ɍ����x�N�g�����Z�o
	D3DXVECTOR3 vecToPlayer = m_pos - posPlayer;

	//�x�N�g���̊p�x���Z�o
	float fAngle = atan2f(vecToPlayer.x, vecToPlayer.z);

	//�p�x��K�p
	m_rot.y = fAngle;
}
