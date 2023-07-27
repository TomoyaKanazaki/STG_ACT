//==========================================
//
//  �i���o�[�N���X(number.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �i���o�[�N���X��`
//==========================================
class CNumber : CObject2D
{
public:
	CNumber(int nPriority = 5); //�R���X�g���N�^
	~CNumber(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetNum(const int nNumber) { m_nNumber = nNumber; }

	//�ÓI�����o�֐�
	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nNumber);

private:

	//�����o�ϐ�
	int m_nNumber; //�\������l

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif