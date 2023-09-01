//==========================================
//
//  �I�u�W�F�N�g3D�N���X(object3D.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_
#include "object.h"
#include "main.h"

//==========================================
//  �I�u�W�F�N�g3D�N���X��`
//==========================================
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 5); //�R���X�g���N�^
	~CObject3D(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max);
	void SetCol(const D3DXCOLOR col);
	void SwitchBillboard(void) { m_bBillboard = !m_bBillboard; }
	float GetHeight(const D3DXVECTOR3 TargetPos);

private:

	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATRIX m_mtxWorld;
	D3DXCOLOR m_col;
	float m_fLength;
	float m_fAngle;
	bool m_bBillboard;

};

#endif
