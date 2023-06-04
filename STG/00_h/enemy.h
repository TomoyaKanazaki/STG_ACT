//==========================================
//
//  エネミークラス(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  エネミークラス定義
//==========================================
class CEnemy : public CObject2D
{
public:
	CEnemy(); //コンストラクタ
	~CEnemy(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static HRESULT Load(void);
	static void UnLoad(void);
	static int GetNum(void) { return m_nNum; }

	//静的メンバ変数
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//メンバ関数
	void Move(void);
	void Rotate(void);
	void Collision(void);

	//メンバ変数
	D3DXVECTOR3 m_move;
	float m_nSpeed;
	float m_fRotMove;
	float m_fRotDest;
	float m_fRotDiff;

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nNum;
};

#endif
