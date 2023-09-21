//==========================================
//
//  背景クラス(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object.h"
#include "layer.h"

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  クラス定義
//==========================================
class CBg : public CObject
{
public:

	//メンバ関数
	CBg(int nPriority = 6);
	~CBg();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CBg *Create(void);

private:

	//モデル情報
	CModel **m_ppModel; //モデル情報
	CLayer::LAYERDATA *m_pLayer; //階層構造情報

};

#endif
