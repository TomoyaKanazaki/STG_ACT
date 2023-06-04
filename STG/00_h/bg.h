//==========================================
//
//  背景クラス(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D_Anim.h"

//==========================================
//  マクロ定義
//==========================================
#define BG_NUM (3) //背景の数

//==========================================
//  背景クラス定義
//==========================================
class CBg : public CObject2D_Anim
{
public:
	CBg(); //コンストラクタ
	~CBg(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static HRESULT Load(void);
	static void UnLoad(void);
	static void Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:
	
	//メンバ変数
	int m_nID; //背景番号
	int m_nSpeed; //スクロール速度

	//静的メンバ変数
	static int m_nNum; //背景数
	static LPDIRECT3DTEXTURE9 m_pTexture[BG_NUM];

};

#endif
