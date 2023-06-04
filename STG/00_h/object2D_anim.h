//==========================================
//
//  アニメーション2Dクラス(object2D_Anim.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_ANIM_H_
#define _OBJECT2D_ANIM_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  アニメーション2Dクラス定義
//==========================================
class CObject2D_Anim : public CObject2D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_U, //横方向のアニメーション
		TYPE_V //縦方向のアニメーション
	}UVTYPE;

	CObject2D_Anim(); //コンストラクタ
	~CObject2D_Anim(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type);

private:

	//メンバ変数
	UVTYPE m_Type;
	int m_nNumPattern; //パターン数
	int m_nAnimPattern; //現在のパターン
	int m_nUpdateFrame; //更新間隔
	int m_nAnimCounter; //アニメーションカウンター
	bool m_bLoop; //ループの有無

};

#endif
