//==========================================
//
//  プレイヤークラス(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  プレイヤークラスの定義
//==========================================
class CPlayer : public CObject2D
{
public:
	CPlayer(int nPriority = 4); //コンストラクタ
	~CPlayer(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

	//静的メンバ変数
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//メンバ関数
	void Move(void);
	void Rotate(void);

	//メンバ変数
	D3DXVECTOR3 m_move;
	float m_fSpeed;
	float m_fRotMove;
	float m_fRotDest;
	float m_fRotDiff;
	bool m_bJunp;

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
