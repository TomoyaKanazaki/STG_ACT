//==========================================
//
//  �w�i�N���X(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_BG (3) //�w�i�̐�

//==========================================
//  �O���錾
//==========================================
class CObject2D_Anim;

//==========================================
//  �w�i�N���X��`
//==========================================
class CBg : public CObject
{
public:
	CBg(); //�R���X�g���N�^
	~CBg(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//�ÓI�����o�֐�
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	
private:

	//�����o�ϐ�
	CObject2D_Anim *m_apObject[MAX_BG];

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];

};

#endif
