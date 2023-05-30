//==========================================
//
//  アニメーションオブジェクト2D(object2D_anim.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_ANIM_H_
#define _OBJECT2D_ANIM_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  アニメーションオブジェクト2Dクラス定義
//==========================================
class CObject2D_Anim : public CObject2D
{
public:
	CObject2D_Anim(); //コンストラクタ
	~CObject2D_Anim(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nAnimPattern);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

	//静的メンバ関数
	static CObject2D_Anim *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nAnimPattern, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//メンバ変数
	int m_nNumPattern; //アニメーションパターン数
	int m_nCountAnim; //アニメーションカウント
	int m_nPatternAnim; //現在のアニメーションパターン

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
