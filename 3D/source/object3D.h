//==========================================
//
//  オブジェクト3Dクラス(object3D.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_
#include "object.h"
#include "main.h"

//==========================================
//  オブジェクト3Dクラス定義
//==========================================
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3); //コンストラクタ
	~CObject3D(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max);
	void SetCol(const D3DXCOLOR col);
	void SwitchBillboard(void) { m_bBillboard = !m_bBillboard; }

private:

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATRIX m_mtxWorld;
	D3DXCOLOR m_col;
	float m_fLength;
	float m_fAngle;
	bool m_bBillboard;

};

#endif
