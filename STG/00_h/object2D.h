//==========================================
//
//  オブジェクト2Dクラス(object2D.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"
#include "main.h"

//==========================================
//  オブジェクト2Dクラス定義
//==========================================
class CObject2D : public CObject
{
public:
	CObject2D(); //コンストラクタ
	~CObject2D(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max);

private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	float m_fLength;
	float m_fAngle;
};

#endif
