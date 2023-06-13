//==========================================
//
//  爆発クラス(explosion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "main.h"
#include "object2D_Anim.h"

//==========================================
//  爆発クラス定義
//==========================================
class CExplosion : public CObject2D_Anim
{
public:
	CExplosion(int nPriority = 2); //コンストラクタ
	~CExplosion(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static HRESULT Load(void);
	static void UnLoad(void);
	static CExplosion *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
