//==========================================
//
//  �p�[�e�B�N���N���X(particle.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "particle.h"
#include "effect.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CParticle::CParticle()
{
	m_range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nEffectNum = 0;
	m_nEffectLife = 0;
	m_nMove = 0;
	m_nLife = 0;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CParticle::~CParticle()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CParticle::Init(void)
{
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CParticle::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CParticle::Update(void)
{
	//�������Ȃ��ꍇ�j������
	if (m_nLife <= 0)
	{
		this->Release();
		return;
	}

	//�G�t�F�N�g�̐���
	for (int nCnt = 0; nCnt < m_nEffectNum; nCnt++)
	{
		//�G�t�F�N�g�̈ړ��ʂ��Z�o
		D3DXVECTOR3 range;
		range.x = (float)((rand() % 200) - 100) * m_range.x;
		range.y = (float)((rand() % 200) - 100) * m_range.y;
		range.z = (float)((rand() % 200) - 100) * m_range.z;
		D3DXVec3Normalize(&range, &range);
		range.x *= m_nMove;
		range.y *= m_nMove;
		range.z *= m_nMove;

		//�G�t�F�N�g�𐶐�
		if (nullptr == (CEffect::Create(m_pos, m_size, m_col, m_nEffectLife, range)))
		{
			return;
		}
	}

	//���������炷
	m_nLife--;
}

//==========================================
//  �`�揈��
//==========================================
void CParticle::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 range, D3DXCOLOR col, int nEffectNum, int nEffectLife, int nMove, int nLife)
{
	//�C���X�^���X����
	CParticle *pParticle = NULL;

	//NULL�`�F�b�N
	if (pParticle == NULL)
	{
		//���������m��
		pParticle = new CParticle;
	}

	//�e��X�e�[�^�X��ݒ�
	pParticle->m_pos = pos;
	pParticle->m_size = size;
	pParticle->m_range = range;
	pParticle->m_col = col;
	pParticle->m_nEffectNum = nEffectNum;
	pParticle->m_nEffectLife = nEffectLife;
	pParticle->m_nMove = nMove;
	pParticle->m_nLife = nLife;

	//������
	if (pParticle != NULL)
	{
		pParticle->Init();
	}

	return pParticle;
}
