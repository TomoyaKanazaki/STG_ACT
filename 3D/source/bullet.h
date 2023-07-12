//==========================================
//
//  バレットクラス(bullet.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  バレットクラス定義
//==========================================
class CBullet : public CObject3D
{
public:
	CBullet(int nPriority = 4); //コンストラクタ
	~CBullet(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);

private:

	typedef struct
	{
		int aInfo[2]; // 0 : Priority, 1 : ID
		int nCounter;
	}Homing;

	//メンバ変数
	D3DXVECTOR3 m_move;
	int m_nLife;
	Homing m_Target;

};

#endif
