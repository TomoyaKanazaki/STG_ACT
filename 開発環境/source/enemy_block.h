//==========================================
//
//  止める敵のクラス(enemy_block.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_BLOCK_H_
#define _ENEMY_BLOCK_H_
#include "main.h"
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Block : public CEnemy
{
public:

	CEnemy_Block(int nPriority = 4); //コンストラクタ
	~CEnemy_Block(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ関数
	void Block(void);

	//メンバ変数
	D3DXVECTOR3 m_posDef;

	//静的メンバ変数
	const static float mc_fBlock;

};

#endif
