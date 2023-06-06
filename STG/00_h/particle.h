//==========================================
//
//  �p�[�e�B�N���N���X(particle.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"
#include "object.h"

//==========================================
//  �p�[�e�B�N���N���X��`
//==========================================
class CParticle : public CObject
{
public:
	CParticle(); //�R���X�g���N�^
	~CParticle(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 range, D3DXCOLOR col, int nEffectNum, int nEffectLife, int nMove, int nLife);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_range; //���������G�t�F�N�g�̈ړ��ʊ
	D3DXCOLOR m_col; //��������G�t�F�N�g�̐F
	int m_nEffectNum; //1f�ɔ�������G�t�F�N�g�̐�
	int m_nEffectLife; //��������G�t�F�N�g�̎���
	int m_nMove; //�ړ���
	int m_nLife; //�p�[�e�B�N���{�̂̎���

};

#endif
