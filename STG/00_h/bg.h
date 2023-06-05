//==========================================
//
//  背景クラス(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_BG (3) //背景の数

//==========================================
//  前方宣言
//==========================================
class CObject2D_Anim;

//==========================================
//  背景クラス定義
//==========================================
class CBg : public CObject
{
public:
	CBg(); //コンストラクタ
	~CBg(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//静的メンバ関数
	static HRESULT Load(void);
	static void UnLoad(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	
private:

	//メンバ変数
	CObject2D_Anim *m_apObject[MAX_BG];

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];

};

#endif
