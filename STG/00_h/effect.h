//==========================================
//
//  �G�t�F�N�g�N���X(effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  �G�t�F�N�g�N���X��`
//==========================================
class CEffect : public CObject2D
{
public:
	CEffect(); //�R���X�g���N�^
	~CEffect(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static HRESULT Load(void);
	static void UnLoad(void);
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nLife);
	static int GetNum(void) { return m_nNum; }

private:

	//�����o�ϐ�
	int m_nLife;

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nNum;

};

#endif
