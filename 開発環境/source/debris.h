//==========================================
//
//  スペースデブリ(debris.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _DEBRIS_H_
#define _DEBRIS_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CDebris : public CEnemy
{
public:

	CDebris(int nPriority = 4); //コンストラクタ
	~CDebris(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CDebris *Create();

private:

	//メンバ変数
	D3DXVECTOR3 m_Rotate;

};

#endif
