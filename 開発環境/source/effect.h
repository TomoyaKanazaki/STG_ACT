//==========================================
//
//  �G�t�F�N�g�N���X(effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �G�t�F�N�g�N���X��`
//==========================================
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = 6); //�R���X�g���N�^
	~CEffect(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col, int nLife);
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col, int nLife, D3DXVECTOR3 move);
	static int GetNum(void) { return m_nNum; }

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_vecDeffSize; //�f�t�H���g�T�C�Y
	int m_nLife;
	float m_fLifeRatio; //�����̍ő�l�ɂ�����P�P��

	//�ÓI�����o�ϐ�
	static int m_nNum;

};

#endif
