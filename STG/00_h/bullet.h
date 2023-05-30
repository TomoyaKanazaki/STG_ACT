//==========================================
//
//  弾クラス(bullet.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  弾クラスの定義
//==========================================
class CBullet : public CObject2D
{
public:
	CBullet(); //コンストラクタ
	~CBullet(); //デストラクタ

	//メンバ変数宣言
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

	//静的メンバ変数
	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//メンバ変数
	D3DXVECTOR3 m_move;
	float m_fSpeed;
	int m_nLife;

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nNum;

};

#endif
