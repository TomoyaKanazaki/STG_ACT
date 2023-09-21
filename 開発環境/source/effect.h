//==========================================
//
//  エフェクトクラス(effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "object3D.h"

//==========================================
//  エフェクトクラス定義
//==========================================
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = 6); //コンストラクタ
	~CEffect(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col, int nLife);
	static CEffect *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, D3DXCOLOR col, int nLife, D3DXVECTOR3 move);
	static int GetNum(void) { return m_nNum; }

private:

	//メンバ変数
	D3DXVECTOR3 m_vecDeffSize; //デフォルトサイズ
	int m_nLife;
	float m_fLifeRatio; //寿命の最大値における１単位

	//静的メンバ変数
	static int m_nNum;

};

#endif
