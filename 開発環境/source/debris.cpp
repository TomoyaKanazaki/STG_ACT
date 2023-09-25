//==========================================
//
//  �X�y�[�X�f�u��(debris.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "debris.h"
#include "model.h"
#include "motion.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CDebris::CDebris(int nPriority) : CEnemy(nPriority)
{
	m_Rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  �f�X�g���N�^
//==========================================
CDebris::~CDebris()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CDebris::Init(void)
{
	//��]�ʂ�ݒ�
	m_Rotate = D3DXVECTOR3
	(
		(float)(rand() % 628 - 314),
		(float)(rand() % 628 - 314),
		(float)(rand() % 628 - 314)
	);
	D3DXVec3Normalize(&m_Rotate, &m_Rotate);

	//�p�x��ݒ�
	m_rot = D3DXVECTOR3
	(
		(float)(rand() % 628 - 314) * 0.01f,
		(float)(rand() % 628 - 314) * 0.01f,
		(float)(rand() % 628 - 314) * 0.01f
	);

	//�ʒu��ݒ�
	m_pos = D3DXVECTOR3
	(
		(float)(rand() % 6000 - 3000),
		(float)(rand() % 6000 - 3000),
		(float)(rand() % 6000 - 3000)
	);

	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_DEBRIS);

	//�K�w�\�����𐶐�
	int nLayer = rand() % 3 + 1;
	m_pLayer = CLayer::Set((CLayer::LAYERS)nLayer);

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

	return CEnemy::Init();
}

//==========================================
//  �I������
//==========================================
void CDebris::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CDebris::Update(void)
{
	//��]
	m_rot += m_Rotate * 0.005f;

	//�p�x�̕␳
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z = -D3DX_PI;
	}
	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z = D3DX_PI;
	}

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CDebris::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  ��������
//==========================================
CDebris * CDebris::Create()
{
	//�C���X�^���X����
	CDebris *pDebris = NULL;

	//NULL�`�F�b�N
	if (pDebris == NULL)
	{
		//���������m��
		pDebris = new CDebris;
	}

	//������
	if (pDebris != NULL)
	{
		pDebris->Init();
	}

	//�|�C���^��Ԃ�
	return pDebris;
}
