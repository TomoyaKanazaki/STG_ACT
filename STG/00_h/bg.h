//==========================================
//
//  背景クラス(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_BG (3)

//==========================================
//  背景クラス定義
//==========================================
class CBg : public CObject2D
{
public:
	CBg(); //コンストラクタ
	~CBg() override; //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	CBg Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//メンバ変数
	float m_fSpeed;

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
