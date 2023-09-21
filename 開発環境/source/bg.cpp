//==========================================
//
//  �w�i�̃N���X(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "model.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CBg::CBg(int nPriority) : CObject(nPriority)
{
	m_ppModel = NULL;
	m_pLayer = NULL;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBg::~CBg()
{

}

//==========================================
//  ������
//==========================================
HRESULT CBg::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(CObject::TYPE_BG);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::BG_LAYER);

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

	return S_OK;
}

//==========================================
//  �I��
//==========================================
void CBg::Uninit(void)
{
	//���f���̃|�C���^��j��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	Release();
}

//==========================================
//  �X�V
//==========================================
void CBg::Update(void)
{
	//�p�x���X�V
	m_rot.x += 0.0001f;
	m_rot.y += 0.0002f;
	m_rot.z += 0.0003f;

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

	m_ppModel[0]->SetRot(m_rot);
}

//==========================================
//  �`��
//==========================================
void CBg::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CBg *CBg::Create(void)
{
	//�C���X�^���X����
	CBg *pBg = NULL;

	//NULL�`�F�b�N
	if (pBg == NULL)
	{
		//���������m��
		pBg = new CBg;
	}

	//������
	if (pBg != NULL)
	{
		pBg->Init();
	}

	//�|�C���^��Ԃ�
	return pBg;
}
