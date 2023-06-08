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
	CBullet(int nPriority = 3); //コンストラクタ
	~CBullet(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static HRESULT Load(void);
	static void UnLoad(void);
	static int GetNum(void) { return m_nNum; }
	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);

private:

	//メンバ関数
	bool CollisionEnemy(void);

	//メンバ変数
	D3DXVECTOR3 m_move;
	float m_fSpeed;
	int m_nLife;

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nNum;

};

#endif
