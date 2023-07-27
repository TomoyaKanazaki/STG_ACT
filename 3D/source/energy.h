//==========================================
//
//  �G�l���M�[�N���X(energy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENERGY_H_
#define _ENERGY_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �G�l���M�[�N���X��`
//==========================================
class CEnergy : public CObject2D
{
public:
	CEnergy(); //�R���X�g���N�^
	~CEnergy(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Add(void) { m_fEnergy += m_fAdd; }
	bool IsMax(void) { return m_fEnergy >= m_fMax; }
	bool IsMin(void) { return m_fEnergy <= 0.0f; }

	//�ÓI�����o�֐�
	static CEnergy *Create(const D3DXVECTOR3 pos, const float fWidth);

private:

	//�����o�ϐ�
	float m_fEnergy;
	float m_fBaseHight; //��ʒu

	//�ÓI�����o�֐�
	const static float m_fMax;
	const static float m_fAdd;

};

#endif
