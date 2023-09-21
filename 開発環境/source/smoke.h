//==========================================
//
//  ���̃N���X(smoke.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SMOKE_H_
#define _SMOKE_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CSmoke : public CObject3D
{
public:
	CSmoke(int nPriority = 7); //�R���X�g���N�^
	~CSmoke(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CSmoke *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, int nLife);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_vecDeffSize; //�f�t�H���g�T�C�Y
	int m_nLife;
	float m_fLifeRatio; //�����̍ő�l�ɂ�����P�P��

};

#endif
