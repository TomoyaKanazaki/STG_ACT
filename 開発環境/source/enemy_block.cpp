//==========================================
//
//  �ǖ�(enemy_block.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_block.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "player.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CEnemy_Block::mc_fBlock = 300.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Block::CEnemy_Block(int nPriority) : CEnemy(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Block::~CEnemy_Block()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Block::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_BLOCK_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::BLOCK_LAYER);

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

	//�����ʒu��ۑ�����
	m_posDef = m_pos;

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Block::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Block::Update(void)
{
	//�e�ɂȂ�Ȃ�����ʒu���Œ肷��
	if (this->GetType() != TYPE_BULLET_ENEMY)
	{
		m_pos = m_posDef;
	}

	//�v���C���[������
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();
	D3DXVECTOR3 vecToPlayer = posPlayer - m_pos;
	m_rot.y = atan2f(-vecToPlayer.x, -vecToPlayer.z);

	//�u���b�N
	Block();

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Block::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �G���~�߂鏈��
//==========================================
void CEnemy_Block::Block(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�����̃A�h���X���擾
		CObject *pObj = this->GetNext();

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_BULLET_ENEMY && pObj != this) //�G�̏ꍇ
			{
				//���݂̓G�Ǝ��������ԃx�N�g�����擾����
				D3DXVECTOR3 posObj = pObj->GetPos();
				D3DXVECTOR3 vecToObj = m_pos - posObj;

				//�x�N�g���̑傫�����Z�o
				float fLength = (vecToObj.x * vecToObj.x) + (vecToObj.z * vecToObj.z);

				//�ڐG�͈͓��ɂ����ꍇ
				if (fLength < mc_fBlock * mc_fBlock)
				{
					pObj->SetType(TYPE_NORMAL_ENEMY);
					pObj->SetPos(pObj->GetOldPos());
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}

}
