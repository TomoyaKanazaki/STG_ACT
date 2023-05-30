//==========================================
//
//  �I�u�W�F�N�g2D�N���X(object2D.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"
#include "main.h"

//==========================================
//  �I�u�W�F�N�g2D�N���X��`
//==========================================
class CObject2D : public CObject
{
public:
	CObject2D(); //�R���X�g���N�^
	~CObject2D(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void) { return m_pVtxBuff; }
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	//�ÓI�����o�֐�
	static CObject2D *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	float m_fLength;
	float m_fAngle;
};

#endif
