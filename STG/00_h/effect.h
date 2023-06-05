//==========================================
//
//  エフェクトクラス(effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "object2D.h"

//==========================================
//  エフェクトクラス定義
//==========================================
class CEffect : public CObject2D
{
public:
	CEffect(); //コンストラクタ
	~CEffect(); //デストラクタ

	//メンバ関数
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static HRESULT Load(void);
	static void UnLoad(void);
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nLife);
	static int GetNum(void) { return m_nNum; }

private:

	//メンバ変数
	D3DXVECTOR3 m_vecDeffSize; //デフォルトサイズ
	D3DXVECTOR3 m_move;
	int m_nLife;
	float m_fLifeRatio; //寿命の最大値における１単位

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static int m_nNum;

};

#endif
