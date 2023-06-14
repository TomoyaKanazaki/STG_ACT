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
	CEffect(int nPriority = 5); //�R���X�g���N�^
	~CEffect(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXCOLOR col, int nLife);
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);
	static int GetNum(void) { return m_nNum; }

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_vecDeffSize; //�f�t�H���g�T�C�Y
	D3DXVECTOR3 m_move;
	int m_nLife;
	float m_fLifeRatio; //�����̍ő�l�ɂ�����P�P��

	//�ÓI�����o�ϐ�
	static int m_nNum;

};

#endif
