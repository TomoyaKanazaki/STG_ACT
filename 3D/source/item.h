//==========================================
//
//  アイテムクラス(item.h)
//  Author :Tomoya Kanazaki
//
//==========================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  アイテムクラス定義
//==========================================
class CItem : public CObject3D
{
public:
	typedef enum
	{
		ENERGY = 0, //パワーアップアイテム
		SCORE, //スコアアイテム
		ITEMS_MAX
	}ITEMS;

	CItem(); //コンストラクタ
	~CItem(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CItem *Create(D3DXVECTOR3 pos, ITEMS type);

private:

	//メンバ変数
	D3DXVECTOR3 m_move;
	ITEMS m_type;

};

#endif
